/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 11:59:17 by fjimenez          #+#    #+#             */
/*   Updated: 2020/12/10 21:01:03 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_arg_exit(t_test *tst, t_shell *pcs)
{(void)tst;
	int i;
	int bool;

    system("leaks minishell");
	if (pcs->cmp[1])
	{
		i = -1;
		bool = 0;
		while(pcs->cmp[1][++i])
		{
			if (!ft_isdigit(pcs->cmp[1][i]))
				bool = 1;
		}
		if (bool)
		{
			ft_putendl_fd("exit", 1);
			ft_putstr_fd("\033[1;31m[Minishell]: ", 1);
			ft_putstr_fd(pcs->cmp[1], 1);
			ft_putendl_fd(": numeric argument required", 1);
			exit(-1);
		}
		else
			exit(ft_atoi(pcs->cmp[1]));

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