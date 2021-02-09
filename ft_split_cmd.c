/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 16:48:04 by fernando          #+#    #+#             */
/*   Updated: 2021/01/28 17:47:01 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_split_quotes(char *s, t_test *t)
{
	if (s[t->i] == 34 && !t->d_qu && !t->s_qu)
		t->d_qu = 1;
	if (s[t->i] == 34 && t->d_qu)
		t->d_qu = 0;
	if (s[t->i] == 39 && !t->d_qu && !t->s_qu)
		t->s_qu = 1;
	if (s[t->i] == 39 && t->s_qu)
		t->s_qu = 0;
}

static int	ft_wordcount(char *s, char c, t_test *t)
{
	while (s[++t->i] != '\0')
	{
		ft_split_quotes(s, t);
		if (s[t->i] == c && !t->d_qu && !t->s_qu)
		{
			while (s[t->i] == c)
				t->i++;
			t->count++;
		}
		if (s[t->i] == 92)
		{
			t->i++;
			if (s[t->i] == c && s[t->i + 1] == 0)
				break ;
		}
		if (s[t->i] == 0)
			break ;
	}
	if (s[t->i - 1] != c && !t->s_qu && !t->d_qu)
		t->count++;
	return (t->count);
}

static int	ft_wordlen(char *s, char c)
{
	t_test t;

	t.d_qu = 0;
	t.s_qu = 0;
	t.i = -1;
	while (s[++t.i])
	{
		ft_aux_loop_quotes(s, &t);
		if (s[t.i] == c && !t.s_qu && !t.d_qu)
			break ;
		if (s[t.i] == 92)
			t.i++;
		if (s[t.i] == 0)
			return (t.i);
	}
	return (t.i);
}

static char	**splitter(char *s, char c, int slot)
{
	int		i;
	int		j;
	char	**t;
	int		len;

	i = 0;
	t = ft_calloc((slot + 1), sizeof(char*));
	while (*s != '\0' && i < slot)
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

char		**ft_split_cmd(char *s, char c)
{
	char	**t;
	int		slot;
	t_test	ts;

	ts.count = 0;
	ts.d_qu = 0;
	ts.s_qu = 0;
	ts.i = -1;
	if (!s)
		return (NULL);
	if (ft_strcmp(s, "") == 0)
	{
		if (!(t = malloc(sizeof(char*))))
			return (NULL);
		*t = NULL;
		return (t);
	}
	slot = ft_wordcount(s, c, &ts);
	if (!(t = splitter(s, c, slot)))
		return (NULL);
	return (t);
}
