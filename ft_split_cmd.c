/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 16:48:04 by fernando          #+#    #+#             */
/*   Updated: 2021/01/13 18:14:50 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_wordcount(char *s, char c)
{
	int count;

	count = 0;
	while (*s)
	{
		ft_getcount_aux(&s);
		if (*s == 92 && *(s + 1) == 92)
			s++;
		else if (*s == 92 && *(s + 1) == c)
			s++;
		if (*s == '\0')
			return (count);
		if (*s && (*(s - 1) != c && *s == c))
			count++;
		s++;
	}
	if (*(s - 1) != c)
		count++;
	return (count);
}

static int	ft_wordlen(char *s, char c)
{
	int count;

	count = 0;
	while (*s != '\0' && *s != c)
	{
		ft_wordlen_aux(&s, &count);
		if (*s == 92 && *(s + 1) == 92)
		{
			s++;
			count++;
		}
		else if (*s == 92 && *(s + 1) == c)
		{
			s++;
			count++;
		}
		count++;
		if (*s == 0)
			return (count);
		s++;
	}
	return (count);
}

static char	**splitter(char const *s, char c)
{
	int		i;
	int		j;
	char	**t;
	int		len;

	i = 0;
	t = ft_calloc((ft_wordcount((char*)s, c) + 1), sizeof(char*));
	while (*s != '\0')
	{
		while (*s == c)
			s++;
		j = 0;
		len = (ft_wordlen((char*)s, c) + 1);
		t[i] = ft_calloc(len, sizeof(char));
		while (--len && *s != '\0')
		{
			t[i][j] = *s;
			j++;
			s++;
		}
		t[i][j] = '\0';
		i++;
	}
	t[i] = NULL;
	return (t);
}

char		**ft_split_cmd(char const *s, char c)
{
	char	**t;

	if (!s)
		return (NULL);
	if (ft_strcmp(s, "") == 0)
	{
		if (!(t = malloc(sizeof(char*))))
			return (NULL);
		*t = NULL;
		return (t);
	}
	if (!(t = splitter(s, c)))
		return (NULL);
	return (t);
}
