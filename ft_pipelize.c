/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipelize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 08:22:48 by fjimenez          #+#    #+#             */
/*   Updated: 2021/02/01 21:18:21 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_return(int status, t_shell *p)
{
	if (WIFEXITED(status))
		p->ret = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		p->ret = WTERMSIG(status);
		if (p->ret == 2)
		{
			p->ret = 130;
			p->is_child = 1;
		}
		if (p->ret == 3)
		{
			p->ret = 131;
			p->is_child = 2;
		}
	}
}

void		ft_wait_pcs(t_shell *p)
{
	int i;
	int status;

	status = 0;
	i = 0;
	while (i < p->pids)
	{
		waitpid(-1, &status, 0);
		ft_return(status, p);
		g_status = p->ret;
		i++;
	}
	ft_free_int_tab(p->pipes);
}

static void	ft_run_pcs_aux(int n, t_shell *p, t_dup *redirs)
{
	if (p->pipes && p->pipes[n] && p->pipes[n][1] > 1)
	{
		redirs->out = p->pipes[n][1];
		redirs->ispipe[1] = 1;
	}
	if (p->pipes && n > 0 && p->pipes[n - 1] && p->pipes[n - 1][0] > 1)
	{
		redirs->in = p->pipes[n - 1][0];
		redirs->ispipe[0] = 1;
	}
	if (!ft_check_redir(redirs, p->pipesplit[n]))
	{
		ft_free_tab(p->cmp);
		ft_close_pipes(p, n);
		return ;
	}
	ft_change_dollar(p, redirs, n);
	ft_check_fork(p, redirs);
	ft_free_tab(p->cmp);
	ft_free_tab(p->upper);
	ft_close_pipes(p, n);
}

static void	ft_run_pcs(int n, t_shell *p)
{
	t_dup	redirs;
	char	*tmp;
	char	*aux;

	tmp = ft_strtrim(p->pipesplit[n], " \t");
	free(p->pipesplit[n]);
	p->pipesplit[n] = tmp;
	aux = ft_realloc_str(p->pipesplit[n], -1, 13);
	if (aux == NULL || p->pipesplit[n][0] == 0)
	{
		if (aux == NULL)
			ft_print_error("ADMIN: ", NULL, "Multilines are not allowed");
		free(aux);
		return ;
	}
	free(aux);
	p->cmp = ft_split_cmd(p->pipesplit[n], ' ');
	if (p->cmp == NULL)
		exit(1);
	ft_bzero(&redirs, sizeof(redirs));
	ft_run_pcs_aux(n, p, &redirs);
}

int			ft_pipelize(int n, t_shell *p)
{
	ft_run_pcs(n, p);
	if (p->pipesplit[n + 1])
		ft_pipelize(n + 1, p);
	return (0);
}
