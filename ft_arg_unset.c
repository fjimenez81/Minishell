/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <fjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 20:14:59 by fernando          #+#    #+#             */
/*   Updated: 2020/07/20 16:52:15 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_strstr(char *str, char *to_find)
{
	int i;
	int j;

	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while (to_find[j] == str[i + j])
		{
			if (to_find[j + 1] == '\0')
				return (str + i);
			j++;
		}
		i++;
	}
	return (0);
}

static void ft_unset_aux(char **aux, int i, int j)
{
	char *unset;
	char *tmp;
	char **split;
	
	tmp = ft_strjoin(aux[j], "=");
	split = ft_split(g_envp[i], '=');
	unset = ft_strstr(g_envp[i], tmp);
	if (unset != NULL)
	{
		if (!ft_strcmp(split[0], aux[j]))
			ft_memmove(g_envp[i], "", ft_strlen(g_envp[i]));
	}
	free(tmp);
	ft_free_tab(split);
}

int ft_arg_unset(char *vars)
{
	int i;
	int j;
	char **aux;
	
	aux = ft_split(vars, ' ');
	i = -1;
	if (aux[1] == NULL)
        return (1);
	else if (ft_len_tab(aux) > 1)
	{
		while (g_envp[++i])
		{
			j = 0;
			while (++j < ft_len_tab(aux))
				ft_unset_aux(aux, i, j);
		}
		ft_free_tab(aux);
		return (1);
	}
	return (0);
}