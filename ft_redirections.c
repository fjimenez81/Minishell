/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <fjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 15:13:48 by fjimenez          #+#    #+#             */
/*   Updated: 2020/08/02 19:09:36 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ft_redir_fd(t_shell *pcs, int flags, char *dir, int *i)
{
	//int		std_out;
	char    *dupout;
	char	*dollar;

	while (ft_isspace(pcs->redir[*i]))
		*i += 1;
	//pcs->std_out = dup(1);
	if (!ft_strcmp(dir, "<"))
	{
		pcs->in = ft_realloc_str(pcs->redir, ft_len_char(pcs->redir), 2);
		if ((pcs->fd = open(pcs->in, O_RDONLY)) < 0)
		{
			ft_putstr_fd(pcs->in, 1);
			pcs->in = NULL;
			ft_putstr_fd(" : No existe el archivo o directorio\n", 1);
		}
		dollar = ft_cutstr(pcs->redir, "echo", ft_strlen(pcs->redir));
		dupout = ft_realloc_str(dollar, -1, 1);
		ft_putendl_fd(dupout, 1);
		dup2(pcs->std_in, 1);
	}
	else
	{
		pcs->out = ft_realloc_str(pcs->redir, ft_len_char(pcs->redir), 2);
		pcs->fd = open(pcs->out, flags, 0644);
		if (!ft_strcmp(pcs->cmp[0], "echo"))
		{
			dollar = ft_cutstr(pcs->redir, "echo", ft_strlen(pcs->redir));
			dupout = ft_realloc_str(dollar, -1, 1);
			dup2(pcs->fd, STDOUT_FILENO);//Pone el standar output en modo escritura
			ft_putendl_fd(dupout, 1);//Y por eso no printa en pantalla y lo escribe en el archivo
			dup2(pcs->std_out, 1);//Devuelve el standar output a su modo original
		}
	}
	close(pcs->fd);
}

static void ft_check_redir_aux(t_shell *pcs, int *i, int quotes)
{
	if ((pcs->redir[*i] == '\"' || pcs->redir[*i] == '\"') &&
		pcs->redir[*i - 1] != '\\' && quotes == 0)
		quotes = 1;
	else if ((pcs->redir[*i] == '\"' || pcs->redir[*i] == '\"') &&
		pcs->redir[*i - 1] != '\\' && quotes == 1)
		quotes = 0;
	else if (pcs->redir[*i] == '>' && quotes == 0)
	{
		pcs->bool_redir = 1;
		*i += 1;
		if (pcs->redir[*i] == '>')
		{
				*i += 1;
				ft_redir_fd(pcs, O_RDWR | O_CREAT | O_APPEND, ">>", &*i);
		}
		else
			ft_redir_fd(pcs, O_TRUNC | O_RDWR | O_CREAT, ">", &*i);
		*i += ft_strlen(pcs->redir) - *i;
	}
	else if (pcs->redir[*i] == '<' && quotes == 0)
	{
		pcs->bool_redir = 1;
		*i += 1;
		ft_redir_fd(pcs, O_RDONLY, "<", &*i);
		*i += ft_strlen(pcs->redir) - *i;
	}
}

void ft_check_redir(t_shell *pcs, int j)
{
	int i;
	int quotes;
	
	i = -1;
	quotes = 0;
	pcs->redir = pcs->pipesplit[j];
	while (pcs->redir[++i])
		ft_check_redir_aux(pcs, &i, quotes);
	if (pcs->bool_redir == 1)
		exit(127);
}
