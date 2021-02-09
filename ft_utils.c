/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/23 16:53:06 by fernando          #+#    #+#             */
/*   Updated: 2021/01/31 21:00:14 by fjimenez         ###   ########.fr       */
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

char	*ft_first_ap(const char *s, int c)
{
	char *first;

	first = NULL;
	if (*s == c)
		return (char*)s;
	while (*s++)
	{
		if (*s == c)
		{
			first = (char*)s;
			break ;
		}
	}
	if (first)
		return (first);
	if (c == '\0')
		return ((char*)s);
	return (0);
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
