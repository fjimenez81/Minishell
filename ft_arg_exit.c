/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 11:59:17 by fjimenez          #+#    #+#             */
/*   Updated: 2021/02/08 11:40:10 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_print_exit(t_test *t, t_shell *pcs, int bool)
{
	int out;

	out = ft_atoi(pcs->cmp[1]);
	if (pcs->args > 2 && !bool)
	{
		ft_print_error(NULL, "exit: ", "too many arguments");
		free(t->aux);
		t->bool = 1;
		return ;
	}
	if (bool == 1)
	{
		ft_print_error(pcs->cmp[1], "exit: ", ": numeric argument required");
		free(t->aux);
		exit(-1);
	}
	free(t->aux);
	exit(out);
}

static void	ft_exit_aux(t_test *t, t_shell *pcs)
{
	int i;
	int bool;

	i = -1;
	bool = 0;
	t->aux = ft_realloc_str(pcs->pipesplit[pcs->n], -1, 0);
	ft_free_tab(pcs->cmp);
	pcs->cmp = ft_split_cmd(t->aux, ' ');
	while (pcs->cmp[1][++i])
	{
		if (i == 0 && pcs->cmp[1][i] == '-')
			i++;
		if (!ft_isdigit(pcs->cmp[1][i]))
			bool = 1;
	}
	ft_print_exit(t, pcs, bool);
}

void		ft_arg_exit(t_shell *pcs)
{
	t_test t;

	t.bool = 0;
	if (pcs->args > 1)
	{
		if (pcs->cmp[1][0] != '<' && pcs->cmp[1][0] != '>')
		{
			ft_putendl_fd("\033[1;31mexit", 1);
			ft_exit_aux(&t, pcs);
		}
	}
	if (!t.bool && pcs->n_pipe == 1)
	{
		ft_putendl_fd("\033[1;31mexit", 1);
		//system("leaks minishell");
		exit(g_status);
	}
}
