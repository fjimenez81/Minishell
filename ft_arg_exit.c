/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 11:59:17 by fjimenez          #+#    #+#             */
/*   Updated: 2020/12/11 10:24:29 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_free_all(t_test *t, t_shell *pcs)
{
	ft_free_tab(pcs->cmp);
	ft_free_tab(t->cmd);
	free(t->line);
	free(pcs);
}

static void	ft_print_exit_two(t_test *t, t_shell *pcs, int j, int bool)
{
	if (pcs->args > 2 && !bool)
	{
		ft_putstr_fd("\033[1;31m[Minishell]: exit", 1);
		ft_putendl_fd(": too many arguments", 1);
		if (j == pcs->n_pipe - 1)
		{
			free(t->aux);
			ft_free_all(t, pcs);
			exit(1);
		}
	}
}

static void	ft_print_exit(t_test *t, t_shell *pcs, int j, int bool)
{
	ft_print_exit_two(t, pcs, j, bool);
	if (bool == 1)
	{
		ft_putstr_fd("\033[1;31m[Minishell]: exit: ", 1);
		ft_putstr_fd(pcs->cmp[1], 1);
		ft_putendl_fd(": numeric argument required", 1);
		if (j == pcs->n_pipe - 1)
		{
			free(t->aux);
			ft_free_all(t, pcs);
			exit(-1);
		}
	}
	else if (j == pcs->n_pipe - 1)
	{
		free(t->aux);
		ft_free_all(t, pcs);
		exit(ft_atoi(pcs->cmp[1]));
	}
}

static void	ft_exit_aux(t_test *t, t_shell *pcs, int j)
{
	int i;
	int bool;

	i = -1;
	bool = 0;
	t->aux = ft_realloc_str(t, pcs->pipesplit[j], -1, 0);
	ft_free_tab(pcs->cmp);
	pcs->cmp = ft_split_cmd(t->aux, ' ');
	while (pcs->cmp[1][++i])
	{
		if (!ft_isdigit(pcs->cmp[1][i]))
			bool = 1;
	}
	ft_print_exit(t, pcs, j, bool);
}

void		ft_arg_exit(t_test *t, t_shell *pcs, int i)
{
	if (!ft_strcmp(pcs->cmp[0], "exit"))
		ft_check_redir(t, pcs, i, 1);
	if (i == pcs->n_pipe - 1)
		ft_putendl_fd("\033[1;31mexit", 1);
	if (pcs->args > 1)
	{
		if (pcs->cmp[1][0] != '<' || pcs->cmp[1][0] != '>')
			ft_exit_aux(t, pcs, i);
	}
	if (g_minish && i == pcs->n_pipe - 1)
	{
		if (g_quit && g_minish->exit != 127)
			exit(1);
		else if (g_minish->exit > 129 && WEXITSTATUS(g_minish->status) != 127)
			exit(g_minish->exit);
		else
			exit(WEXITSTATUS(g_minish->status));
	}
	if (i == pcs->n_pipe - 1)	
		exit(0);
}
