/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <fjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 10:37:02 by fjimenez          #+#    #+#             */
/*   Updated: 2020/10/05 10:41:25 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_multiple_redir(t_shell *pcs, t_test *tst)
{
	int i;
	int k;

	i = 0;
	k = -1;
	if (tst->check_fdot > 0)
	{
		if (!(tst->pid = malloc(sizeof(pid_t) * tst->check_fdot)))
			return ;
		tst->check_pid = 0;
		while (++i < tst->check_fdot)
		{
			tst->pid[i] = fork();
			if (tst->pid[i] == 0)
			{
				dup2(pcs->fd_out[i], STDOUT_FILENO);
				tst->check_pid = 1;
				break ;
			}
		}
	}
}

void		ft_file_out(t_shell *pcs, t_test *tst, int flags)
{
	pcs->out = ft_realloc_str(tst, pcs->redir, tst->i - 1, 2);
	if (tst->fdot_j == 0)
		if (!(pcs->fd_out = (int*)malloc(sizeof(int) * tst->check_fdot)))
			return ;
	if ((pcs->fd_out[tst->fdot_j] = open(pcs->out, flags, 0600)) == -1)
	{
		ft_putstr_fd("minishell : no such file or directory: ", 1);
		ft_putendl_fd(pcs->out, 1);
		exit(1);
	}
	pcs->flag_out = 1;
	tst->fdot_j++;
	dup2(pcs->fd_out[0], STDOUT_FILENO);
}

static void	ft_get_redir_aux(t_shell *pcs, t_test *tst)
{
	int		get;
	char	*line;
	char	*tmp;

	if ((get = get_next_line(0, &line)) != 0)
	{
		tmp = ft_strjoin(line, "\n");
		tst->get_redir = ft_strjoin(tst->get_redir, tmp);
		free(line);
		free(tmp);
	}
	if (!get)
	{
		tst->get_redir = ft_strjoin(tst->get_redir, line);
		ft_multiple_redir(pcs, tst);
		ft_putstr_fd(tst->get_redir, 1);
		free(line);
		free(tst->get_redir);
		exit(0);
	}
}

void		ft_get_redir(t_shell *pcs, t_test *tst)
{
	tst->get_redir = "\0";
	if (pcs->cmp[0][0] == '>')
	{
		while (1)
			ft_get_redir_aux(pcs, tst);
	}	
}
