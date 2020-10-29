/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 16:48:04 by fernando          #+#    #+#             */
/*   Updated: 2020/10/29 17:43:45 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	getcount(char *s, int count, int c)
{
	while (*s)
	{
		if (*s == '\"')
		{
			s++;
			while (*s && *s != '\"')
				s++;
		}
		if (*s == '\'')
		{
			s++;
			while (*s && *s != '\'')
				s++;
		}
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

static int	ft_wordcount(char *s, char c)
{
	int count;

	count = 0;
	if (*s == '\0')
		return (0);
	s++;
	if (*s == '\0' && *(s - 1) != c)
		return (1);
	count = getcount(s, count, c);
	return (count);
}

static int	ft_wordlen(char *s, char c)
{
	int count;

	count = 0;
	while (*s != '\0' && *s != c)
	{
		if (*s == '\"')
		{
			count++;
			s++;
			while (*s && *s != '\"' && (count = count + 1))
				s++;
		}
		if (*s == '\'')
		{
			s++;
			count++;
			while (*s && *s != '\'' && (count = count + 1))
				s++;
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
	t = (char**)malloc(sizeof(char*) * (ft_wordcount((char*)s, c) + 1));
	while (*s != '\0')
	{
		while (*s == c)
			s++;
		j = 0;
		len = (ft_wordlen((char*)s, c) + 1);
		t[i] = (char*)malloc(len * sizeof(char));
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
	char	*trimmed;
	char	totrim[2];
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
	totrim[0] = c;
	totrim[1] = '\0';
	if (!(trimmed = ft_strtrim(s, totrim)))
		return (NULL);
	if (!(t = splitter(trimmed, c)))
		return (NULL);
	free(trimmed);
	return (t);
}
