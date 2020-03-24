/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 19:36:04 by fjimenez          #+#    #+#             */
/*   Updated: 2019/11/28 10:10:57 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static	int		ft_contador(char const *str, char c)
{
	int		word_len;
	size_t	cont;

	word_len = 0;
	cont = 0;
	while (*str)
	{
		if (!word_len && *str != c)
			cont++;
		word_len = (*str == c) ? 0 : 1;
		str++;
	}
	return (cont);
}

static	int		ft_word_len(char const *str, char c)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while (str[i] == c)
		i++;
	while (str[i] != c && str[i] != '\0')
	{
		i++;
		len++;
	}
	return (len);
}

char			**ft_split(const char *str, char c)
{
	int		i;
	int		j;
	int		k;
	char	**s;

	if (!str || !(s = (char**)malloc(sizeof(*s) * (ft_contador(str, c) + 1))))
		return (NULL);
	i = -1;
	j = 0;
	while (++i < ft_contador(str, c))
	{
		k = 0;
		if (!(s[i] = ft_calloc(ft_word_len(&str[j], c) + 1, 1)))
			s[i] = NULL;
		while (str[j] == c)
			j++;
		while (str[j] != c && str[j])
			s[i][k++] = str[j++];
		s[i][k] = '\0';
	}
	s[i] = 0;
	return (s);
}
