/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_forks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 11:27:24 by fjimenez          #+#    #+#             */
/*   Updated: 2021/02/08 21:00:27 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_arg_pwd(t_shell *p)
{
	char pwd[PATH_MAX];

	if (!ft_strcmp(p->cmp[0], "pwd"))
	{
		ft_putendl_fd(getcwd(pwd, -1), p->fd);
		return (0);
	}
	return (1);
}

static void	ft_run_no_builtins(t_shell *p, t_dup *redirs,
	int forked)
{
	if (forked == 1)
	{
		ft_close_and_dup(p, redirs);
		ft_arg_exe(p);
		p->is_child = 0;
		exit(127);
	}
	else
	{
		if (fork() == 0)
		{
			ft_close_and_dup(p, redirs);
			ft_arg_exe(p);
			p->is_child = 0;
			exit(127);
		}
		else
			p->pids++;
	}
}

static void	ft_check_args_aux(t_shell *p)
{
	p->bool = 0;
	if (!ft_strcmp(p->cmp[0], "echo") && (p->bool = 1))
		p->ret = ft_arg_echo(p);
	else if (!ft_isupper(p->upper[0]) && !ft_strcmp(p->cmp[0], "export") &&
			(p->bool = 1))
		p->ret = ft_arg_export(p);
	else if ((!ft_strcmp(p->cmp[0], "env") || !ft_ck_rd_envp(p, "env")) &&
			(p->bool = 1))
		p->ret = ft_arg_env(p);
	else if ((!ft_strcmp(p->cmp[0], "pwd") || !ft_ck_rd_envp(p, "pwd")) &&
			(p->bool = 1))
		p->ret = ft_arg_pwd(p);
}

static void	ft_check_args(t_shell *p, t_dup *redirs, int forked)
{
	p->fd = 1;
	if (redirs->out > 0)
		p->fd = redirs->out;
	if (p->cmp[0] == NULL || (!ft_strlen(p->cmp[0]) &&
		(ft_strcmp(p->upper[0], "\"\"") &&
		ft_strcmp(p->upper[0], "\'\'"))) || p->ret == 1)
		return ;
	ft_check_args_aux(p);
	ft_only_path(p);
	if (!ft_isupper(p->upper[0]) && !ft_strcmp(p->cmp[0], "unset"))
		p->ret = ft_arg_unset(p);
	else if (!ft_strcmp(p->cmp[0], "cd"))
	{
		if (ft_isupper(p->upper[0]))
			p->ret = 0;
		else
			p->ret = ft_arg_cd(p);
	}
	else if (!ft_isupper(p->upper[0]) && !ft_strcmp(p->cmp[0], "exit"))
		ft_arg_exit(p);
	else if (!p->bool)
		ft_run_no_builtins(p, redirs, forked);
}

void		ft_check_fork(t_shell *p, t_dup *redirs)
{
	ft_change_case(&p->cmp[0]);
	signal(SIGINT, &ft_ctrl_process);
	if (redirs->ispipe[0] == 1 || redirs->ispipe[1] == 1)
	{
		if (fork() == 0)
		{
			ft_check_args(p, redirs, 1);
			exit(0);
		}
		else
			p->pids++;
	}
	else
	{
		ft_check_args(p, redirs, 0);
		g_status = p->ret;
	}
	ft_close_fd(redirs->in);
	ft_close_fd(redirs->out);
}
