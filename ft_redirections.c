/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 15:13:48 by fjimenez          #+#    #+#             */
/*   Updated: 2020/10/07 18:16:50 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_read_fdin(t_shell *pcs, t_test *tst)
{
	int		read;
	char	*line;

	if (pcs->cmp[0][0] == '<')
	{
		while ((read = get_next_line(pcs->fd_in[tst->fdin_k], &line)) != 0)
		{
			ft_putendl_fd(line, 1);
			free(line);
		}
		tst->fdin_k++;
		close(pcs->fd_in[tst->fdin_k]);
		if (tst->fdin_k == tst->check_fdin)
			exit(0);
	}
	pcs->flag_in = 1;
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
			ft_putstr_fd("minishell : no such file or directory: ", 1);
			ft_putendl_fd(pcs->in, 1);
			exit(1);
		}
		ft_read_fdin(pcs, tst);
		//dup2(pcs->fd_in, 0);
	}
	else
		ft_file_out(pcs, tst, flags);
}

void		ft_ck_redir_two(t_test *tst, t_shell *pcs, int pass)
{
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
	if (!pass)
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
		if (pass == 1)
		{
			tst->i += 1;
			ft_redir_fd(pcs, O_RDONLY, "<", tst);
			if (pcs->redir[tst->i] == '<')
				tst->i -= 1;
		}
		if (!pass)
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
	pcs->flag_in = 0;
	pcs->flag_out = 0;
	tst->fdot_j = 0;
	tst->fdin_k = 0;
	if (!pass)
	{
		tst->check_fdot = 0;
		tst->check_fdin = 0;
	}
	while (pcs->redir[++tst->i])
		ft_check_redir_aux(tst, pcs, &quotes, pass);
	return (1);
}
