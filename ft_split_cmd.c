/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 16:48:04 by fernando          #+#    #+#             */
/*   Updated: 2021/01/11 20:03:08 by fjimenez         ###   ########.fr       */
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
		if (*s && (*(s - 1) == c && *s == c))
			s++;
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
	while (*s != '\0')
	{
		ft_wordlen_aux((char*)s, &count);
		if (*s == 92 && *(s + 1) == c)
		{
			count++;
			s++;
		}
		else if (*s == c && *(s - 1) != 92)
			break ;
		count++;
		s++;
	}
	return (count);
}

static char	**splitter(char const *s, char c)
{
	int		i;
	int		j;
	char	**tmp;
	int		len;

	i = 0;
	tmp = ft_calloc((ft_wordcount((char*)s, c) + 1), sizeof(char*));
	while (*s != '\0')
	{
		while (*s == c)
			s++;
		j = 0;
		len = (ft_wordlen((char*)s, c) + 1);
		tmp[i] = ft_calloc(len, sizeof(char));
		while (--len && *s != '\0')
		{
			tmp[i][j] = *s;
			j++;
			s++;
		}
		tmp[i][j] = '\0';
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}

char		**ft_split_cmd(char const *s, char c)
{
	char	**tmp;

	if (!s)
		return (NULL);
	if (ft_strcmp(s, "") == 0)
	{
		if (!(tmp = malloc(sizeof(char*))))
			return (NULL);
		*tmp = NULL;
		return (tmp);
	}
	if (!(tmp = splitter(s, c)))
		return (NULL);
	return (tmp);
}
