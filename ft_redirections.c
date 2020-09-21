/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <fjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 15:13:48 by fjimenez          #+#    #+#             */
/*   Updated: 2020/09/21 17:14:30 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ft_redir_fd(t_shell *pcs, int flags, char *dir, t_test *tst)
{
	while (ft_isspace(pcs->redir[tst->i]))
		tst->i += 1;
	if (!ft_strcmp(dir, "<"))
	{
		pcs->in = ft_realloc_str(tst, pcs->redir, ft_len_char(pcs->redir), 2);
		if ((pcs->fd_in = open(pcs->in, O_RDONLY)) == -1)
		{
			ft_putstr_fd("minishell : no such file or directory: ", 1);
			ft_putendl_fd(pcs->in, 1);
			pcs->in = NULL;
		}
		pcs->flag_in = 1;
		dup2(pcs->fd_in, 0);
	}
	else
	{
		pcs->out = ft_realloc_str(tst, pcs->redir, ft_len_char(pcs->redir), 2);
		if ((pcs->fd_out = open(pcs->out, flags, 0600)) == -1)
		{
			ft_putstr_fd("minishell : no such file or directory: ", 1);
			ft_putendl_fd(pcs->out, 1);
			pcs->out = NULL;
		}
		pcs->flag_out = 1;
		dup2(pcs->fd_out, STDOUT_FILENO);
	}
}

static void ft_check_redir_aux(t_test *tst, t_shell *pcs, int *quotes)
{
	if ((pcs->redir[tst->i] == '\"' || pcs->redir[tst->i] == '\'') &&
		pcs->redir[tst->i - 1] != '\\' && *quotes == 0)
		*quotes = 1;
	else if ((pcs->redir[tst->i] == '\"' || pcs->redir[tst->i] == '\'') &&
		pcs->redir[tst->i - 1] != '\\' && *quotes == 1)
		*quotes = 0;
	else if (pcs->redir[tst->i] == '>' && *quotes == 0)
	{
		tst->i += 1;
		if (pcs->redir[tst->i] == '>')
		{
				tst->i += 1;
				ft_redir_fd(pcs, O_RDWR | O_CREAT | O_APPEND, ">>", tst);
		}
		else
			ft_redir_fd(pcs, O_TRUNC | O_RDWR | O_CREAT, ">", tst);
		tst->i += ft_strlen(pcs->redir) - tst->i;
	}
	else if (pcs->redir[tst->i] == '<' && *quotes == 0)
	{
		tst->i += 1;
		ft_redir_fd(pcs, O_RDONLY, "<", tst);
		tst->i += ft_strlen(pcs->redir) - tst->i;
	}
}

int ft_check_redir(t_test *tst, t_shell *pcs, int j)
{
	int quotes;
	
	tst->i = -1;
	quotes = 0;
	pcs->redir = pcs->pipesplit[j];
	while (pcs->redir[++tst->i])
		ft_check_redir_aux(tst, pcs, &quotes);
	return (1);
}
