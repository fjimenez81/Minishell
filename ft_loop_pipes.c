/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <fjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 11:35:17 by fjimenez          #+#    #+#             */
/*   Updated: 2020/09/14 12:03:56 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_loop_pipes_aux(t_shell *pcs, t_test *tst, int j)
{
	pcs->previus = pcs;
	if(!ft_strcmp(pcs->cmp[0], "exit"))//no funciona con pipes al cerrar deja abierto los procesos
	{
		system("leaks minishell");
		exit(0);
	}
	else if (!ft_strcmp(pcs->cmp[0], "cd") || !ft_strcmp(pcs->cmp[0], "~"))//no fuciona en pipes por eso lo pongo por delante
		ft_arg_cd(pcs);
	else if(!ft_strcmp(pcs->cmp[0], "export"))//Parece que algunas funciones tienen que ir antes de pipes
		ft_arg_export(tst, pcs, j);
	else if(!ft_strcmp(pcs->cmp[0], "unset"))
		ft_arg_unset(pcs->pipesplit[j]);
	else
		ft_check_pipes(pcs, tst, j);
	ft_free_tab(pcs->cmp);
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
	while (++j < ft_len_tab(aux))
	{
		pcs->pipesplit = aux;
		tmp = ft_strtrim(pcs->pipesplit[j], " \t");
		free(pcs->pipesplit[j]);
		pcs->pipesplit[j] = tmp;
		pcs->cmp = ft_split_cmd(pcs->pipesplit[j], ' ');
		pcs->args = ft_len_tab(pcs->cmp);
		ft_loop_pipes_aux(pcs, tst, j);
	}
	ft_free_tab(aux);
	free(pcs);
}
