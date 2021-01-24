/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 11:27:24 by fjimenez          #+#    #+#             */
/*   Updated: 2021/01/22 21:01:10 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_execute_aux(t_shell *pcs, t_test *tst, int i)
{
	char pwd[PATH_MAX];

	ft_check_redir(tst, pcs, i, 1);
	if (!ft_ck_rd_envp(pcs, tst, "pwd") ||
		!ft_strcmp(pcs->cmp[0], "pwd") || !ft_strcmp(pcs->cmp[0], "PWD"))
	{
		ft_putendl_fd(getcwd(pwd, -1), 1);
		return (0);
	}
	return (1);
}

static int	ft_execute(t_shell *pcs, int i, t_test *tst)
{
	if (tst->status == 1)
		return (1);
	if (tst->status == 126)
		return (126);
	if (!ft_strcmp(pcs->cmp[0], "$PATH"))
		return (127);
	if (!ft_execute_aux(pcs, tst, i))
		return (0);
	else if (!ft_ck_rd_envp(pcs, tst, "export") ||
		(!ft_strcmp(pcs->cmp[0], "export") && pcs->cmp[1][0] == '>') ||
		(!ft_strcmp(pcs->cmp[0], "export") &&
		(!ft_strcmp(pcs->cmp[1], ">") || !ft_strcmp(pcs->cmp[1], ">>"))))
		return (ft_sort_export());
	else if ((!ft_ck_rd_envp(pcs, tst, "env") ||
		!ft_strcmp(pcs->cmp[0], "env") || !ft_strcmp(pcs->cmp[0], "ENV")) &&
		pcs->bool_redir == 0)
		return (ft_arg_env(pcs));
	if (!ft_strcmp(pcs->cmp[0], "echo") || !ft_strcmp(pcs->cmp[0], "ECHO"))
		return (ft_arg_echo(pcs, tst, i));
	else if (!tst->bool)
		return (ft_arg_exe(pcs, tst, i));
	return (0);
}

static void	ft_pipe_son(t_shell *pcs, t_test *tst, int j)
{
	if (pcs->n_pipe > 1)
	{
		close(pcs[j].pipes[READ]);//Cierra el extremo de lectura no necesario del pipe actual
		dup2(pcs[j].pipes[WRITE], STDOUT);//Copia la salida extandar al extremo de escritura del pipe actual
		if (j > 0)
			dup2(pcs[j - 1].pipes[READ], STDIN);//Copia la entrada extandar al extremo de lectura del pipe previo
	}
	if (j == pcs->n_pipe - 1)
		dup2(pcs->std_out, STDOUT);//Copia la salida extandar a std_out para mostrarlo en pantalla
	pcs->ret = ft_execute(pcs, j, tst);
	ft_close_fd(pcs);
	ft_free_all(tst, pcs);
	exit(pcs->ret);
}

static void	ft_pipe_father(t_shell *pcs, t_test *tst, int j)
{
	if (pcs->n_pipe > 1)
	{
		close(pcs[j].pipes[WRITE]);//El padre va cerrando el extremo de escritura del pipe actual
		if (j == pcs->n_pipe - 1)
			close(pcs[j].pipes[READ]);//El padre cierra el extremo de lectura del ultimo pipe
	}
	waitpid(pcs->pid, &tst->status, WUNTRACED);
	if (WIFEXITED(tst->status))
		pcs->ret = WEXITSTATUS(tst->status);
}

void		ft_check_pipes(t_shell *pcs, t_test *tst, int j)
{
	//pcs->std_in = dup(0);
	pcs->std_out = dup(1);
	if (pcs->n_pipe > 1)
		pipe(pcs[j].pipes);
	ft_cut_pcs(tst);
	pcs->pid = fork();
	if (pcs->pid == 0)
		ft_pipe_son(pcs, tst, j);
	else
		ft_pipe_father(pcs, tst, j);
}
