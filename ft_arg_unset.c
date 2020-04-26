/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernando <fernando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 20:14:59 by fernando          #+#    #+#             */
/*   Updated: 2020/04/26 21:08:36 by fernando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static char	**ft_str_unset(char **dest, char *src, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	//if (*src == '\0')
		//return ((char*)dest);
	while (dest[i] && i < n)
	{
		if (dest[i] == src)
		{
			j = 0;
			while (src != NULL && dest[i + j] == src && (i + j) < n)
			{
				j++;
				if (src == NULL)
					return (dest);
			}
		}
		i++;
	}
	return (0);
}*/

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
			{
				return (str + i);
			}
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
	int len;
	char *unset;

	//if (!(tmp = (char**)malloc(sizeof(char*) * (ft_len_tab(g_envp) + 1))))
		//return (-1);

	len = ft_len_tab(vars);
	i = -1;
	if (args)
	{
		if (vars[1] == NULL)
            return (1);
		else if (ft_len_tab(vars) > 1)
		{
			while (g_envp[++i])
			{
				j = 0;
				while (++j < len)
				{
					unset = ft_strstr(g_envp[i], vars[j]);
					if (unset != NULL)
						ft_memmove(g_envp[i], "", ft_strlen(g_envp[i]));
				}
					
			}
			//ft_memmove(g_envp[j - 1], "", ft_strlen(g_envp[j - 1]));
			//ft_putstr_fd(g_envp[j - 1], 1);
			//ft_free_tab(tmp);
			return (1);
		}
	}
	return (-1);
}