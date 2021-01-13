/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 16:48:04 by fernando          #+#    #+#             */
/*   Updated: 2021/01/13 11:00:40 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static	int	getcount(t_test *t, char *s, int count, int c)
// {
// 	t->k = 0;
// 	while (s[t->k] != '\0')
// 	{
// 		if (s[t->k] == '\"')
// 		{
// 			t->k++;
// 			while (s[t->k] && s[t->k] != '\"')
// 				t->k++;
// 		}
// 		if (s[t->k] == '\'')
// 		{
// 			t->k++;
// 			while (s[t->k] && s[t->k] != '\'')
// 				t->k++;
// 		}
// 		if (s[t->k] == '\0')
// 			return (count);
// 		if (s[t->k] && (s[t->k - 1] != c && s[t->k] == c))
// 			count++;
// 		t->k++;
// 	}
// 	if (s[t->k - 1] != c)
// 		count++;
// 	return (count);
// }

// static int	ft_wordcount(t_test *t, char *s, char c)
// {
// 	int count;

// 	count = 0;
// 	t->k = 0;
// 	if (s[t->k] == '\0')
// 		return (0);
// 	t->k++;
// 	if (s[t->k] == '\0' && s[t->k - 1] != c)
// 		return (1);
// 	count = getcount(t, s, count, c);
// 	return (count);
// }

// static int	ft_wordlen(t_test *t, char *s, char c)
// {
// 	int count;

// 	count = 0;
// 	t->k = 0;
// 	while (s[t->k] != '\0' && s[t->k] != c)
// 	{
// 		if (*s == '\"')
// 		{
// 			count++;
// 			t->k++;
// 			while (s[t->k] && s[t->k] != '\"' && (count = count + 1))
// 				t->k++;
// 		}
// 		if (s[t->k] == '\'')
// 		{
// 			t->k++;
// 			count++;
// 			while (s[t->k] && s[t->k] != '\'' && (count = count + 1))
// 				t->k++;
// 		}
// 		// if (s[t->k] == 92 && s[t->k + 1] == 92)
// 		// {
// 		// 	t->k += 2;
// 		// 	count += 2;
// 		// }
// 		// if (s[t->k] == 92 && s[t->k + 1] == c)
// 		// {
// 		// 	t->k += 2;
// 		// 	count += 2;
// 		// }
// 		count++;
// 		if (s[t->k] == 0)
// 			return (count);
// 		t->k++;
// 	}
// 	return (count);
// }

// static char	**splitter(t_test *t, char const *s, char c)
// {
// 	char	**tmp;
// 	int		len;

// 	t->i = 0;
// 	//t->k = -1;
// 	tmp = ft_calloc((ft_wordcount(t, (char*)s, c) + 1), sizeof(char*));
// 	while (*s != '\0')
// 	{
// 		while (*s == c)
// 			s++;
// 		t->j = 0;
// 		len = (ft_wordlen(t, (char*)s, c) + 1);
// 		tmp[t->i] = ft_calloc(len, sizeof(char));
// 		while (--len && *s != '\0')
// 		{
// 			tmp[t->i][t->j] = *s;
// 			t->j++;
// 			s++;
// 		}
// 		tmp[t->i][t->j] = '\0';
// 		t->i++;
// 	}
// 	tmp[t->i] = NULL;
// 	return (tmp);
// }

// char		**ft_split_cmd(char const *s, char c)
// {
// 	char	**tmp;
// 	t_test	t;

// 	if (!s)
// 		return (NULL);
// 	if (ft_strcmp(s, "") == 0)
// 	{
// 		if (!(tmp = malloc(sizeof(char*))))
// 			return (NULL);
// 		*tmp = NULL;
// 		return (tmp);
// 	}
// 	if (!(tmp = splitter(&t, s, c)))
// 		return (NULL);
// 	return (tmp);
// }

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