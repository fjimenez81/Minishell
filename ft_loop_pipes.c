/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 11:35:17 by fjimenez          #+#    #+#             */
/*   Updated: 2020/12/11 17:05:37 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_comands(t_test *tst)
{
	int		i;
	char	**aux;

	i = -1;
	while (tst->cmd[++i])
	{
		aux = ft_split_cmd(tst->cmd[i], '|');
		ft_loop_pipes(aux, tst);
		ft_free_tab(aux);
	}
}

void	ft_loop_pipes_aux(t_shell *pcs, t_test *tst, int j)
{
	tst->bool = 0;
	if (!ft_strcmp(pcs->cmp[0], "exit") && j == pcs->n_pipe - 1)
		ft_arg_exit(pcs);
	else if ((!ft_strcmp(pcs->cmp[0], "cd") ||
		!ft_strcmp(pcs->cmp[0], "~")) && j == pcs->n_pipe - 1 &&
		pcs->bool_redir == 0 && (tst->bool = 1))
		ft_arg_cd(pcs, tst);
	else if (!ft_strcmp(pcs->cmp[0], "export") &&
		j == pcs->n_pipe - 1 && pcs->bool_redir == 0 && (tst->bool = 1))
		ft_arg_export(tst, pcs, j);
	else if (!ft_strcmp(pcs->cmp[0], "unset") &&
		j == pcs->n_pipe - 1 && (tst->bool = 1))
		ft_arg_unset(pcs, tst);
	ft_check_pipes(pcs, tst, j);
}

void	ft_loop_pipes(char **aux, t_test *tst)
{
	int		j;
	char	*tmp;
	t_shell	*pcs;

	if (!(pcs = ft_calloc(ft_len_tab(aux) + 1, sizeof(t_shell))))
		return ;
	j = -1;
	pcs->ret = EXIT_SUCCESS;
	pcs->n_pipe = ft_len_tab(aux);
	pcs->pipesplit = aux;
	while (++j < pcs->n_pipe)
	{
		tmp = ft_strtrim(pcs->pipesplit[j], " \t");
		free(pcs->pipesplit[j]);
		pcs->pipesplit[j] = tmp;
		if (ft_strlen(pcs->pipesplit[j]) == 0)
			break ;
		pcs->cmp = ft_split_cmd(pcs->pipesplit[j], ' ');
		pcs->args = ft_len_tab(pcs->cmp);
		ft_check_redir(tst, pcs, j, 0);
		ft_loop_pipes_aux(pcs, tst, j);
		ft_free_tab(pcs->cmp);
	}
	free(pcs);
}

// void	ft_loop_pipes(char **aux, t_test *tst)
// {
// 	int		j;
// 	char	*tmp;
// 	t_shell	pcs;

// 	j = -1;
// 	pcs.ret = EXIT_SUCCESS;
// 	pcs.n_pipe = ft_len_tab(aux);
// 	while (++j < pcs.n_pipe)
// 	{
// 		usleep(10000);
// 		pcs.pipesplit = aux;
// 		tmp = ft_strtrim(pcs.pipesplit[j], " \t");
// 		free(pcs.pipesplit[j]);
// 		pcs.pipesplit[j] = tmp;
// 		if (ft_strlen(pcs.pipesplit[j]) == 0)
// 			break ;
// 		pcs.cmp = ft_split_cmd(pcs.pipesplit[j], ' ');
// 		pcs.args = ft_len_tab(pcs.cmp);
// 		ft_check_redir(tst, &pcs, j, 0);
// 		ft_loop_pipes_aux(&pcs, tst, j);
// 		ft_free_tab(pcs.cmp);
// 	}
// 	ft_free_tab(aux);
// }
