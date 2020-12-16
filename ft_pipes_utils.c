/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 10:21:55 by fjimenez          #+#    #+#             */
/*   Updated: 2020/12/16 18:17:28 by fjimenez         ###   ########.fr       */
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
	else if (sig == SIGQUIT)
	{
		g_minish->exit = 131;
		ft_putstr_fd("Quit\n", 1);
	}
}

void	ft_cut_pcs(t_test *tst)
{
	signal(SIGINT, &ft_ctrl_process);
	if (g_quit == 1)
	{
		tst->cheat = 1;
		g_quit = 0;
	}
}

void	ft_close_fd(t_shell *pcs)
{
	if (pcs->flag_out)
	{
		dup2(pcs->std_out, 1);
		pcs->flag_out = 0;
	}
	if (pcs->flag_in)
	{
		dup2(pcs->std_out, 0);
		pcs->flag_in = 0;
	}
}

void	ft_err_exit(t_shell *pcs, t_test *tst, int i)
{
	char *aux;

	if (g_minish->exit > 129 &&
		WEXITSTATUS(g_minish->status) != 127 && !tst->cheat)
		{
			aux = ft_realloc_str(tst, pcs->pipesplit[i], -1, g_minish->exit);
			ft_print_error(aux);
			free(aux);
		}
	else if (tst->cheat)
	{
		aux = ft_realloc_str(tst, pcs->pipesplit[i], -1, 9);
		ft_print_error(aux);
		free(aux);
	}
	else
		ft_print_error(pcs->cmp[0]);
}

int		ft_ck_rd_envp(t_shell *pcs, t_test *tst, char *str)
{
	char	*aux;
	int		len;
	int		i;
	int		check;

	aux = ft_realloc_str(tst, pcs->cmp[0], -1, 1);
	len = ft_strlen(str);
	check = 0;
	i = -1;
	while (pcs->cmp[0][++i])
	{
		if (check == len &&
			(pcs->cmp[0][i] == '>' || pcs->cmp[0][i] == '<'))
			return (0);
		if (aux[i] == str[i])
			check++;
	}
	free(aux);
	return (1);
}
