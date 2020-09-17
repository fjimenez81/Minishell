/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <fjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 11:27:24 by fjimenez          #+#    #+#             */
/*   Updated: 2020/09/17 19:05:16 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_arg_exe(t_shell *pcs, t_test *tst, int i)
{
	char	*join;
	int		exe;
	int		j;

	exe = -1;
	j = 0;
	ft_free_tab(pcs->cmp);
	pcs->cmp = ft_split_cmd(ft_realloc_str
		(tst, pcs->pipesplit[i], -1, 0), ' ');
	while (exe == -1 && j < 3)
	{
		join = ft_strjoin(tst->paths[j], pcs->cmp[0]);
		j++;
		free(join);
		exe = execve(join, pcs->cmp, g_envp);
		if (j == 3 && exe == -1)
		{
				ft_putstr_fd(tst->error, 1);
				ft_putendl_fd(pcs->cmp[0], 1);
				tst->status = 127;
				exit(127);
		}
	}
	return (0);
}

static int	ft_execute(t_shell *pcs, int i, t_test *tst)
{
	char pwd[PATH_MAX];
	int exe;
	
	exe = -1;
	pcs->bool_redir = 0;
	if (!ft_check_redir(tst, pcs, i))
		return (0);
	if (!ft_strcmp(pcs->cmp[0], "pwd") && (exe = 1))
		ft_putendl_fd(getcwd(pwd, -1), 1);
	else if (!ft_strcmp(pcs->cmp[0], "env") && (exe = 1))
		ft_arg_env(pcs);
	else if (!ft_strcmp(pcs->cmp[0], "echo") && (exe = 1))
		ft_arg_echo(pcs, tst, i);
	else if (exe == -1)
		ft_arg_exe(pcs, tst, i);
	return (0);
}

static void	ft_pipe_son(t_shell *pcs, t_test *tst, int j)
{
	dup2(pcs->previus[j].pipes[SIDEIN], STDOUT);
	if (j > 0)
		dup2(pcs->previus[j - 1].pipes[SIDEOUT], STDIN);
	if (j == ft_len_tab(pcs->pipesplit) - 1)
		dup2(pcs->std_out, STDOUT);
	pcs->ret = ft_execute(pcs, j, tst);
	exit(pcs->ret);
}

static void	ft_pipe_father(t_shell *pcs, t_test *tst, int j)
{
	waitpid(pcs->pid, &tst->status, 0);
	if (ft_len_tab(pcs->pipesplit) > 1)
	{
		close(pcs->previus[j].pipes[SIDEIN]);
		if (j == ft_len_tab(pcs->pipesplit))
			close(pcs->previus[j].pipes[SIDEOUT]);
		if (j > 0)
			close(pcs->previus[j - 1].pipes[SIDEOUT]);
		if (WIFEXITED(tst->status))
			pcs->ret = WEXITSTATUS(tst->status);
	}
}

void ft_check_pipes(t_shell *pcs, t_test *tst, int j)
{
    pcs->std_in = dup(0);
	pcs->std_out = dup(1);
	if (ft_len_tab(pcs->pipesplit) > 1)
		pipe(pcs->previus[j].pipes);
	pcs->pid = fork();
	if (pcs->pid == 0)
		ft_pipe_son(pcs, tst, j);
	else
		ft_pipe_father(pcs, tst, j);
}
