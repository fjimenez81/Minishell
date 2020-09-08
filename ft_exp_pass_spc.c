/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exp_pass_spc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <fjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 15:24:25 by fjimenez          #+#    #+#             */
/*   Updated: 2020/09/08 20:13:51 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ft_pass_space_two(char *str, int *i, int *size)
{
	int equal;
	int quotes;

	equal = 0;
	quotes = 0;
	while (str[++*i])
	{
		if (str[*i] == '=' && equal == 0)
			equal = 1;
		if ((str[*i] == '\"' || str[*i] == '\'') && str[*i - 1] != '\\' &&
			equal == 1 && quotes == 0)
			quotes = 1;
		else if ((str[*i] == '\"' || str[*i] == '\'') && str[*i - 1] != '\\' &&
			equal == 1 && quotes == 1)
			quotes = 0;
		if (str[*i] != ' ' && str[*i + 1] == ' ' && str[*i] != '\\' &&
			equal == 1 && quotes == 0)
			equal = 0;
		else if (str[*i] == '\\' && str[*i + 1] == ' ' && quotes == 0 &&
			equal == 1)
		{
			*i += 1;
			*size += 1;
		}
	}
}

static void ft_pass_space_four(t_shell *pcs, char *str, int i)
{
	if (str[i] == '=' && pcs->equal == 0)
		pcs->equal = 1;
	if ((str[i] == '\"' || str[i] == '\'') && str[i - 1] != '\\' &&
		pcs->equal == 1 && pcs->quotes == 0)
		pcs->quotes = 1;
	else if ((str[i] == '\"' || str[i] == '\'') && str[i - 1] != '\\' &&
		pcs->equal == 1 && pcs->quotes == 1)
		pcs->quotes = 0;
	if (str[i] != ' ' && str[i + 1] == ' ' && str[i] != '\\' &&
		pcs->equal == 1 && pcs->quotes == 0)
		pcs->equal = 0;
}

static char *ft_pass_space_three(t_shell *pcs, char *str, char *aux)
{
	int i;
	int j;

	i = -1;
	j = 0;
	pcs->equal = 0;
	pcs->quotes = 0;
	while (str[++i])
	{
		ft_pass_space_four(pcs, str, i);
		if (str[i] == '\\' && str[i + 1] == ' ' &&
			pcs->quotes == 0)// && pcs->equal == 1)
		{
			aux[j] = '\"';
			j++;
			aux[j] = ' ';
			j++;
			aux[j] = '\"';
			i += 2;
			j++;
		}
		aux[j] = str[i];
		j++;	
	}
	return (aux);
}

char *ft_pass_space(t_shell *pcs, char *str)
{
	int i;
	int size;
	char *pass;

	i = -1;
	ft_pass_space_two(str, &i, &size);
	pass = ft_strnew(size + i);
	return (ft_pass_space_three(pcs, str, pass));
}
