/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 11:35:17 by fjimenez          #+#    #+#             */
/*   Updated: 2020/10/08 17:34:41 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_loop_pipes_aux(t_shell *pcs, t_test *tst, int j)
{
	tst->bool = 0;
	if(!ft_strcmp(pcs->cmp[0], "exit") && j == pcs->n_pipe - 1)//no funciona con pipes al cerrar deja abierto los procesos
	{
		system("leaks minishell");
		exit(0);
	}
	else if ((!ft_strcmp(pcs->cmp[0], "cd") ||
		!ft_strcmp(pcs->cmp[0], "~")) && j == pcs->n_pipe - 1 &&
		pcs->bool_redir == 0 && (tst->bool = 1))//no fuciona en pipes por eso lo pongo por delante
		ft_arg_cd(pcs, tst);
	else if(!ft_strcmp(pcs->cmp[0], "export") &&
		j == pcs->n_pipe - 1 && pcs->bool_redir == 0 && (tst->bool = 1))//Parece que algunas funciones tienen que ir antes de pipes
		ft_arg_export(tst, pcs, j);
	else if(!ft_strcmp(pcs->cmp[0], "unset") &&
		j == pcs->n_pipe - 1 && (tst->bool = 1))
		ft_arg_unset(tst, pcs);
	//if (tst->bool == 1)
		//return ;
	ft_check_pipes(pcs, tst, j);
}

void ft_loop_pipes(char **aux, t_test *tst)
{
	int		j;
	char	*tmp;
	t_shell	*pcs;

	if (!(pcs = malloc(sizeof(t_shell) * (ft_len_tab(aux) + 1))))
			return ;
	j = -1;
	pcs->ret = EXIT_SUCCESS;
	pcs->n_pipe = ft_len_tab(aux);
	while (++j < pcs->n_pipe)
	{
		pcs->pipesplit = aux;
		tmp = ft_strtrim(pcs->pipesplit[j], " \t");
		free(pcs->pipesplit[j]);
		pcs->pipesplit[j] = tmp;
		pcs->cmp = ft_split_cmd(pcs->pipesplit[j], ' ');
		pcs->args = ft_len_tab(pcs->cmp);
		ft_check_redir(tst, pcs, j, 0);
		ft_loop_pipes_aux(pcs, tst, j);
		//free(pcs->fd_out);
		//free(pcs->fd_in);
		//free(tst->pid);
		ft_free_tab(pcs->cmp);
	}
	ft_free_tab(aux);
	free(pcs);
}
