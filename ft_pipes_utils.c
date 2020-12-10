/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 10:21:55 by fjimenez          #+#    #+#             */
/*   Updated: 2020/12/10 21:08:44 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_ctrl_process(int sig)
{
	if (sig == SIGINT)
	{
		g_minish->exit = 130;
		g_minish->status = 0;
		g_quit = 0;
		ft_putstr_fd("\n", 1);
	}
	// else if (sig == SIGQUIT)
	// 	ft_putstr_fd("\b\b  \b\b", 1);
}

void		ft_cut_pcs(t_test *tst)
{
	signal(SIGINT, &ft_ctrl_process);
	if (g_quit)
	{
		tst->cheat = 1;
		g_quit = 0;
	}
}

void		ft_close_fd(t_shell *pcs, t_test *tst)
{
	int k;

	k = -1;
	if (pcs->flag_out == 1)
	{
		while (++k < tst->check_fdot)
			close(pcs->fd_out[k]);
		dup2(pcs->std_out, 1);
		pcs->flag_out = 0;
	}
	if (pcs->flag_in)
	{
		dup2(pcs->fd_in[tst->fdin_k], 1);
		pcs->flag_in = 0;
	}
}

void		ft_err_exit(t_shell *pcs, t_test *tst, int i)
{
	if (g_minish->exit == 130 &&
		WEXITSTATUS(g_minish->status) != 127 && !tst->cheat)
	{
		ft_print_error(ft_realloc_str(tst, pcs->pipesplit[i], -1, 5));
	}
	else if (tst->cheat)
	{
		ft_print_error(ft_realloc_str(tst, pcs->pipesplit[i], -1, 9));
		tst->cheat = 0;
	}
	else
	{
		ft_print_error(pcs->cmp[0]);
	}
}
