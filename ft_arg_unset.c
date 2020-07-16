/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <fjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 20:14:59 by fernando          #+#    #+#             */
/*   Updated: 2020/07/14 17:14:51 by fjimenez         ###   ########.fr       */
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

int ft_arg_unset(char *vars)
{
	int i;
	int j;
	char *unset;
	char **aux;

	aux = ft_split_cmd(vars, ' ');
	i = -1;
	if (aux[1] == NULL)
        return (1);
	else if (ft_len_tab(aux) > 1)
	{
		while (g_envp[++i])
		{
			j = 0;
			while (++j < ft_len_tab(aux))
			{
				unset = ft_strstr(g_envp[i], aux[j]);
				if (unset != NULL)
					ft_memmove(g_envp[i], "", ft_strlen(g_envp[i]));
			}
		}
		ft_free_tab(aux);
		return (1);
	}
	return (0);
}