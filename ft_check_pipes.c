/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 11:27:24 by fjimenez          #+#    #+#             */
/*   Updated: 2020/10/07 19:58:25 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_execute_aux(t_shell *pcs, t_test *tst, int i, int *exe)
{
	char pwd[PATH_MAX];

	if (tst->status == 1)
		exit(1);
	ft_check_redir(tst, pcs, i, 1);
	ft_get_redir(pcs, tst);
	ft_multiple_redir(pcs, tst);
	if (!ft_strcmp(pcs->cmp[0], "pwd") && (*exe = 1))
	{
		if (pcs->cmp[1])
		{
			ft_putendl_fd("pwd: too many arguments", 1);
			exit(1);
		}
		else
			ft_putendl_fd(getcwd(pwd, -1), 1);
	}
}

static int	ft_execute(t_shell *pcs, int i, t_test *tst)
{
	int exe;

	exe = 0;
	ft_execute_aux(pcs, tst, i, &exe);
	if (!ft_strcmp(pcs->cmp[0], "env") &&
		pcs->bool_redir == 0 && (exe = 1))
		ft_arg_env(pcs);
	else if (!ft_strcmp(pcs->cmp[0], "echo") && (exe = 1))
		ft_arg_echo(pcs, tst, i);
	else if ((!ft_strcmp(pcs->cmp[0], "export") &&
		(!ft_strcmp(pcs->cmp[1], ">") ||
		!ft_strcmp(pcs->cmp[1], ">>"))) && (exe = 1))
		ft_sort_export();
	else if ((!ft_strcmp(pcs->cmp[0], "export") ||
		!ft_strcmp(pcs->cmp[0], "unset")) && tst->bool == 0)
		tst->bool = 1;
	else if (exe == 0 && !tst->bool)
		ft_arg_exe(pcs, tst, i);
	return (0);
}

static void	ft_pipe_son(t_shell *pcs, t_test *tst, int j)
{
	if (dup2(pcs[j].pipes[SIDEIN], STDOUT) < 0)
	{
		ft_putendl_fd("fatal error", 1);
		return ;
	}
	if (j > 0)
		dup2(pcs[j - 1].pipes[SIDEOUT], STDIN);
	if (j == pcs->n_pipe - 1)
		dup2(pcs->std_out, STDOUT);
	pcs->ret = ft_execute(pcs, j, tst);
	exit(pcs->ret);
}

static void	ft_pipe_father(t_shell *pcs, t_test *tst, int j)
{
	waitpid(pcs->pid, &tst->status, 0);
	if (pcs->n_pipe > 1)
	{
		close(pcs[j].pipes[SIDEIN]);
		if (j == pcs->n_pipe)
			close(pcs[j].pipes[SIDEOUT]);
		if (j > 0)
			close(pcs[j - 1].pipes[SIDEOUT]);
		if (WIFEXITED(tst->status))
			pcs->ret = WEXITSTATUS(tst->status);
	}
}

void		ft_check_pipes(t_shell *pcs, t_test *tst, int j)
{
	int k;

	k = -1;
	pcs->std_in = dup(0);
	pcs->std_out = dup(1);
	if (pcs->n_pipe > 1)
		pipe(pcs[j].pipes);
	pcs->pid = fork();
	if (pcs->pid == 0)
		ft_pipe_son(pcs, tst, j);
	else
		ft_pipe_father(pcs, tst, j);
	if (pcs->flag_out == 1)
	{
		while (++k < tst->check_fdot)
			close(pcs->fd_out[k]);
		dup2(pcs->std_out, 1);
	}
	//if (pcs->flag_in == 1)
		//dup2(pcs->std_out, 0);
}
