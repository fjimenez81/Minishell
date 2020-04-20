/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernando <fernando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 20:14:59 by fernando          #+#    #+#             */
/*   Updated: 2020/04/20 21:17:33 by fernando         ###   ########.fr       */
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

int ft_arg_unset(char **vars, int args)
{
	int i;
	//char **tmp;

	i = -1;
	if (args)
	{
		if (vars[1] == NULL)
            return (1);
		else if (ft_strchr(vars[1], '='))
		{
			//tmp = ft_str_unset(g_envp, vars[1], ft_len_tab(g_envp));
			//ft_putstr_fd(tmp[0], 1);
			return (1);
		}
		else
			return (1);
		
	}
	return (-1);
}