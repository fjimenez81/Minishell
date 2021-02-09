/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 10:21:55 by fjimenez          #+#    #+#             */
/*   Updated: 2021/02/07 19:14:06 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_int_tab(int **arr)
{
	int i;

	i = 0;
	while (arr[i])
		i++;
	while (i >= 0)
	{
		free(arr[i]);
		arr[i] = NULL;
		i--;
	}
	free(arr);
	arr = NULL;
}

void	ft_ctrl_process(int sig)
{
	if (sig == SIGINT)
	{
		g_quit = 0;
		ft_putstr_fd("\n", 1);
	}
	else if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit\n", 1);
	}
}

void	ft_err_exit(t_shell *pcs)
{
	int		i;
	char	*aux;

	i = -1;
	ft_free_tab(pcs->cmp);
	pcs->cmp = ft_split_cmd(pcs->pipesplit[pcs->n], ' ');
	while (pcs->cmp[++i])
	{
		aux = ft_realloc_str(pcs->cmp[i], -1, 0);
		free(pcs->cmp[i]);
		pcs->cmp[i] = aux;
	}
	i = -1;
	while (pcs->cmp[0][++i])
	{
		if (pcs->cmp[0][i] == '/')
		{
			ft_print_error(pcs->cmp[0], NULL, ": No such file or directory");
			return ;
		}
	}
	ft_print_error(pcs->cmp[0], NULL, ": command not found");
}

int		ft_ck_rd_envp(t_shell *pcs, char *str)
{
	char	*aux;
	int		len;
	int		i;
	int		check;

	aux = ft_realloc_str(pcs->cmp[0], -1, 1);
	len = ft_strlen(str);
	check = 0;
	i = -1;
	while (pcs->cmp[0][++i])
	{
		if (check == len &&
			(pcs->cmp[0][i] == '>' || pcs->cmp[0][i] == '<'))
		{
			free(aux);
			return (0);
		}
		if (aux[i] == str[i])
			check++;
	}
	free(aux);
	return (1);
}
