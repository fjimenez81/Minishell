/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_str_aux.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 11:02:40 by fjimenez          #+#    #+#             */
/*   Updated: 2021/01/23 13:58:15 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*ft_join_char(char *s, int c)
{
	int		i;
	char	*res;

	if (!(res = malloc(sizeof(char) * (ft_strlen(s) + 2))))
		return (NULL);
	i = -1;
	while (s[++i])
		res[i] = s[i];
	res[i] = c;
	i++;
	res[i] = '\0';
	return (res);
}

void		ft_aux_loop_quotes(char *s, t_test *t)
{
	while (s[t->i] == 34 || s[t->i] == 39)
	{
		if (s[t->i] == 34 && !t->d_qu && !t->s_qu)
		{
			t->i++;
			t->d_qu = 1;
		}
		if (s[t->i] == 34 && t->d_qu)
		{
			t->i++;
			t->d_qu = 0;
		}
		if (s[t->i] == 39 && !t->s_qu && !t->d_qu)
		{
			t->i++;
			t->s_qu = 1;
		}
		if (s[t->i] == 39 && t->s_qu)
		{
			t->i++;
			t->s_qu = 0;
		}
	}
}

void		ft_realloc_aux_two(char *s, t_test *t)
{
	ft_aux_loop_quotes(s, t);
	if (t->one_dollar)
		t->one_dollar = 0;
	if (t->check_redir)
		t->check_redir = 0;
	else if (s[t->i] == ' ' && (!t->d_qu && !t->s_qu))
	{
		while (ft_isspace(s[t->i]))
			t->i++;
		t->i--;
	}
}
