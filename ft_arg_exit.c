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

static void	ft_exit_aux(t_shell *pcs)
{
	int i;
	int bool;

	i = -1;
	bool = 0;
	while (pcs->cmp[1][++i])
	{
		if (!ft_isdigit(pcs->cmp[1][i]))
			bool = 1;
	}
	if (pcs->args > 2 && !bool)
	{
		ft_putstr_fd("[Minishell]: exit", 1);
		ft_putendl_fd(": too many arguments", 1);
		exit(1);
	}
	if (bool == 1)
	{
		ft_putstr_fd("[Minishell]: exit: ", 1);
		ft_putstr_fd(pcs->cmp[1], 1);
		ft_putendl_fd(": numeric argument required", 1);
		exit(-1);
	}
	else
		exit(ft_atoi(pcs->cmp[1]));
}

void		ft_arg_exit(t_shell *pcs)
{
	system("leaks minishell");
	ft_putendl_fd("\033[1;31mexit", 1);
	if (pcs->args > 1)
	{
		if (pcs->cmp[1][0] == '<' || pcs->cmp[1][0] == '>')
			exit(0);
		else
			ft_exit_aux(pcs);
	}
	if (g_minish)
	{
		if (g_quit && g_minish->exit != 127)
			exit(1);
		else if (g_minish->exit == 130 && WEXITSTATUS(g_minish->status) != 127)
			exit(130);
		else
			exit(WEXITSTATUS(g_minish->status));
	}
	exit(0);
}
