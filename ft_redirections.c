/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 15:13:48 by fjimenez          #+#    #+#             */
/*   Updated: 2020/12/11 15:27:11 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_file_out(t_shell *pcs, t_test *tst, int flags)
{
	pcs->out = ft_realloc_str(tst, pcs->redir, tst->i - 1, 2);
	if (tst->fdot_j == 0)
		if (!(pcs->fd_out = (int*)malloc(sizeof(int) * tst->check_fdot)))
			return ;
	if ((pcs->fd_out[tst->fdot_j] = open(pcs->out, flags, 0600)) == -1)
	{
		ft_putstr_fd("\033[1;31mminishell: ", 1);
		ft_putstr_fd(pcs->out, 1);
		ft_putendl_fd(": No such file or directory", 1);
		exit(1);
	}
	pcs->flag_out = 1;
	if (tst->fdot_j == tst->check_fdot - 1)
		dup2(pcs->fd_out[tst->fdot_j], STDOUT_FILENO);
	tst->fdot_j++;
}

static void	ft_redir_fd(t_shell *pcs, int flags, char *dir, t_test *tst)
{
	while (ft_isspace(pcs->redir[tst->i]))
		tst->i += 1;
	if (!ft_strcmp(dir, "<"))
	{
		if (tst->fdin_k == 0)
			if (!(pcs->fd_in = (int*)malloc(sizeof(int) * tst->check_fdin)))
				return ;
		pcs->in = ft_realloc_str(tst, pcs->redir, tst->i - 1, 2);
		if ((pcs->fd_in[tst->fdin_k] = open(pcs->in, flags)) == -1)
		{
			ft_putstr_fd("\033[1;31mminishell: ", 1);
			ft_putstr_fd(pcs->in, 1);
			ft_putendl_fd(": No such file or directory", 1);
			exit(1);
		}
		dup2(pcs->fd_in[tst->fdin_k], 0);
		pcs->flag_in = 1;
	}
	else
		ft_file_out(pcs, tst, flags);
}

void		ft_ck_redir_two(t_test *tst, t_shell *pcs, int pass)
{
	pcs->flag_out = 1;
	if (pass)
	{
		tst->i++;
		if (pcs->redir[tst->i] == '>')
		{
			tst->i++;
			ft_redir_fd(pcs, O_RDWR | O_CREAT | O_APPEND, ">>", tst);
		}
		else
			ft_redir_fd(pcs, O_TRUNC | O_RDWR | O_CREAT, ">", tst);
		if (pcs->redir[tst->i] == '>')
			tst->i--;
	}
	else
	{
		tst->check_fdot++;
		if (pcs->redir[tst->i] == '>')
			tst->i++;
	}
	pcs->bool_redir = 1;
}

static void	ft_check_redir_aux(t_test *tst, t_shell *pcs,
	int *quotes, int pass)
{
	if ((pcs->redir[tst->i] == '\"' || pcs->redir[tst->i] == '\'') &&
		pcs->redir[tst->i - 1] != '\\' && *quotes == 0)
		*quotes = 1;
	else if ((pcs->redir[tst->i] == '\"' || pcs->redir[tst->i] == '\'') &&
		pcs->redir[tst->i - 1] != '\\' && *quotes == 1)
		*quotes = 0;
	else if (pcs->redir[tst->i] == '>' && pcs->redir[tst->i - 1] != '\\' &&
		*quotes == 0)
		ft_ck_redir_two(tst, pcs, pass);
	else if (pcs->redir[tst->i] == '<' && pcs->redir[tst->i - 1] != '\\' &&
		*quotes == 0)
	{
		pcs->flag_in = 1;
		if (pass == 1)
		{
			tst->i += 1;
			ft_redir_fd(pcs, O_RDONLY, "<", tst);
			if (pcs->redir[tst->i] == '<')
				tst->i -= 1;
		}
		else
			tst->check_fdin++;
		pcs->bool_redir = 1;
	}
}

int			ft_check_redir(t_test *tst, t_shell *pcs, int j, int pass)
{
	int quotes;

	tst->i = -1;
	quotes = 0;
	pcs->redir = pcs->pipesplit[j];
	pcs->bool_redir = 0;
	tst->fdot_j = 0;
	tst->fdin_k = 0;
	pcs->flag_out = 0;
	pcs->flag_in = 0;
	if (!pass)
	{
		tst->check_fdot = 0;
		tst->check_fdin = 0;
	}
	while (pcs->redir[++tst->i])
		ft_check_redir_aux(tst, pcs, &quotes, pass);
	return (1);
}
