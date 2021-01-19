/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/23 16:53:06 by fernando          #+#    #+#             */
/*   Updated: 2020/12/11 13:12:09 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2 && *s1 != 0)
	{
		++s1;
		++s2;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int		ft_len_tab(char **args)
{
	int i;

	i = 0;
	while (*args++)
		i++;
	return (i);
}

void	*ft_memalloc(size_t size)
{
	unsigned char *mem;

	if (!(mem = (unsigned char*)malloc(sizeof(size_t) * size)))
		return (NULL);
	ft_bzero(mem, size);
	return (mem);
}

void	ft_free_tab(char **str)
{
	int i;

	i = 0;
	while (str[i])
		free(str[i++]);
	(str) ? free(str) : 0;
}

char	**ft_add_str(char **s)
{
	int		i;
	char	**aux;

	if (!s || (!(aux = (char**)malloc(sizeof(char*) * (ft_len_tab(s) + 2)))))
		return (NULL);
	i = -1;
	while (s[++i])
		aux[i] = ft_join_char(s[i], '/');
	aux[i] = ft_strdup("");
	i++;
	aux[i] = NULL;
	ft_free_tab(s);
	return (aux);
}
