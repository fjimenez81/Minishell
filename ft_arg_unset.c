/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernando <fernando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 20:14:59 by fernando          #+#    #+#             */
/*   Updated: 2020/05/08 12:31:59 by fernando         ###   ########.fr       */
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

int ft_arg_unset(char **vars, int args)
{
	int i;
	int j;
	char *unset;

	i = -1;
	if (args)
	{
		if (vars[1] == NULL)
            return (1);
		else if (args > 1)
		{
			while (g_envp[++i])
			{
				j = 0;
				while (++j < args)
				{
					unset = ft_strstr(g_envp[i], vars[j]);
					if (unset != NULL)
						ft_memmove(g_envp[i], "", ft_strlen(g_envp[i]));
				}
			}
			return (1);
		}
	}
	return (-1);
}