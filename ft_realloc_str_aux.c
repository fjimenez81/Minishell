/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_str_aux.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 11:02:40 by fjimenez          #+#    #+#             */
/*   Updated: 2021/02/08 19:47:38 by fjimenez         ###   ########.fr       */
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

char		*ft_tilde_redir(t_test *t, char *res)
{
	char	*tmp;
	char	*aux;

	tmp = ft_get_var("HOME=", 0);
	if (tmp != NULL)
	{
		aux = ft_strjoin(res, tmp);
		free(res);
		res = aux;
		t->i++;
		t->tilde = 1;
	}
	free(tmp);
	return (res);
}

static int	ft_quotes_aux(char *s, t_test *t)
{
	if (s[t->i] == 39 && s[t->i + 1] == 39)
		t->i += 2;
	if (s[t->i] == 39 && !t->s_qu && !t->d_qu)
	{
		t->i++;
		t->s_qu = 1;
	}
	else if ((s[t->i] == 39 && !t->s_qu && t->d_qu) ||
		(s[t->i] == 39 && t->d_qu && t->s_qu))
		return (0);
	else if (s[t->i] == 39 && t->s_qu)
	{
		t->i++;
		t->s_qu = 0;
	}
	return (1);
}

void		ft_aux_loop_quotes(char *s, t_test *t)
{
	while (s[t->i] && (s[t->i] == 34 || s[t->i] == 39))
	{
		if (s[t->i] == 34 && s[t->i + 1] == 34 && !t->d_qu && !t->s_qu)
			t->i += 2;
		if (s[t->i] == 34 && t->d_qu && s[t->i + 1] == '$')
			t->cheat = 1;
		if (s[t->i] == 34 && !t->d_qu && !t->s_qu)
		{
			t->i++;
			t->d_qu = 1;
		}
		else if ((s[t->i] == 34 && t->s_qu && !t->d_qu) ||
			(s[t->i] == 34 && t->d_qu && t->s_qu))
			break ;
		else if (s[t->i] == 34 && t->d_qu)
		{
			t->i++;
			t->d_qu = 0;
		}
		if (!ft_quotes_aux(s, t))
			break ;
	}
}

void		ft_realloc_aux_two(char *s, t_test *t)
{
	ft_aux_loop_quotes(s, t);
	if (t->one_dollar)
		t->one_dollar = 0;
	if (t->check_redir)
		t->check_redir = 0;
	if (t->slash)
		t->slash = 0;
	if (t->tilde)
		t->tilde = 2;
	if (s[t->i] == 92 && s[t->i + 1] != 92 && (t->d_qu || t->s_qu))
	{
		if (s[t->i + 1] == 34 || s[t->i + 1] == 39)
			t->i++;
		else if (s[t->i + 1] == '$')
		{
			t->i++;
			t->one_dollar = 1;
		}
		else
			t->slash = 1;
	}
}
