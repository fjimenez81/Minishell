/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 11:27:24 by fjimenez          #+#    #+#             */
/*   Updated: 2020/10/29 16:46:23 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_execute_aux(t_shell *pcs, t_test *tst, int i)
{
	char pwd[PATH_MAX];

	ft_check_redir(tst, pcs, i, 1);
	ft_get_redir(pcs, tst);
	ft_multiple_redir(pcs, tst);
	if (!ft_ck_rd_envp(pcs, tst, "pwd") ||
		(!ft_strcmp(pcs->cmp[0], "pwd") && !pcs->cmp[1]))
	{
		ft_putendl_fd(getcwd(pwd, -1), 1);
		return (0);
	}
	if (!ft_strcmp(pcs->cmp[0], "pwd") && pcs->cmp[1][0] != '>' &&
		pcs->cmp[1][0] != '<')
	{
		ft_putendl_fd("pwd: too many arguments", 1);
		return (0);
	}
	return (1);
}

int ft_ck_rd_envp(t_shell *pcs, t_test *tst, char *str)
{
	char	*aux;
	int		len;
	int		i;
	int		check;

	aux = ft_realloc_str(tst, pcs->cmp[0], -1, 1);
	len = ft_strlen(str);
	check = 0;
	i = -1;
	while (pcs->cmp[0][++i])
	{
		if (check == len &&
			(pcs->cmp[0][i] == '>' || pcs->cmp[0][i] == '<'))
			return (0);
		if (aux[i] == str[i])
			check++;
	}
	return (1);
}

static int	ft_execute(t_shell *pcs, int i, t_test *tst)
{
	
	if (tst->status == 1)
		return (1);
	if (!ft_execute_aux(pcs, tst, i))
		return (1);
	else if (!ft_ck_rd_envp(pcs, tst, "export") ||
		(!ft_strcmp(pcs->cmp[0], "export") && pcs->cmp[1][0] == '>') ||
		(!ft_strcmp(pcs->cmp[0], "export") &&
		(!ft_strcmp(pcs->cmp[1], ">") || !ft_strcmp(pcs->cmp[1], ">>"))))
		return (ft_sort_export());
	else if (!ft_ck_rd_envp(pcs, tst, "env") || (!ft_strcmp(pcs->cmp[0], "env") &&
		pcs->bool_redir == 0))
		return (ft_arg_env(pcs));
	else if (!ft_strcmp(pcs->cmp[0], "echo"))
		return (ft_arg_echo(pcs, tst, i));
	else if (!tst->bool)
		return (ft_arg_exe(pcs, tst, i));
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
