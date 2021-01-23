/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 15:53:45 by fjimenez          #+#    #+#             */
/*   Updated: 2021/01/23 15:55:19 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redir_in_aux(t_shell *pcs, t_test *tst)
{
	tst->k = tst->i;
	pcs->in = ft_realloc_str(tst, pcs->redir, tst->i - 1, 2);
	if (ft_strchr(pcs->redir + tst->k, '$') &&
		!ft_strchr(pcs->redir + tst->k, 34) &&
		!ft_strchr(pcs->redir + tst->k, 39))
	{
		tst->aux = ft_realloc_str(tst, pcs->redir, tst->k - 1, 4);
		ft_putstr_fd("\033[1;31m[Minishell]: ", 1);
		ft_putstr_fd(tst->aux, 1);
		ft_putendl_fd(": ambiguous redirect", 1);
		free(pcs->in);
		free(tst->aux);
		ft_free_all(tst, pcs);
		exit(1);
	}
}

void	ft_redir_out_aux(t_shell *pcs, t_test *tst)
{
	tst->k = tst->i;
	pcs->out = ft_realloc_str(tst, pcs->redir, tst->i - 1, 2);
	if (ft_strchr(pcs->redir + tst->k, '$') &&
		!ft_strchr(pcs->redir + tst->k, 34) &&
		!ft_strchr(pcs->redir + tst->k, 39))
	{
		tst->aux = ft_realloc_str(tst, pcs->redir, tst->k - 1, 4);
		ft_putstr_fd("\033[1;31m[Minishell]: ", 1);
		ft_putstr_fd(tst->aux, 1);
		ft_putendl_fd(": ambiguous redirect", 1);
		free(tst->aux);
		free(pcs->out);
		ft_free_all(tst, pcs);
		exit(1);
	}
}
