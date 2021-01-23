/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 17:14:03 by fjimenez          #+#    #+#             */
/*   Updated: 2021/01/23 12:07:52 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_only_dollar(char *s, t_test *t)
{
	if (s[t->i] == '$' && (s[t->i + 1] == 34 || s[t->i + 1] == 39 ||
		s[t->i + 1] == 92))
	{
		if (s[t->i + 1] == 34 && !t->d_qu)
		{
			t->d_qu = 1;
			t->i += 2;
		}
		if (s[t->i + 1] == 39 && !t->d_qu)
		{
			t->s_qu = 1;
			t->i += 2;
		}
		if ((s[t->i + 1] == 39 && t->d_qu) ||
			s[t->i + 1] == 92)
			t->one_dollar = 1;
	}
}

static int	ft_aux_loop_two(char *str, t_test *tmp)
{
	ft_realloc_aux_two(str, tmp);
	if (((str[tmp->i] == ' ' || str[tmp->i] == '<' || str[tmp->i] == '>') &&
		!tmp->check_redir && !tmp->d_qu && !tmp->s_qu &&
		tmp->cut == 2) || (str[tmp->i] == '=' && tmp->cut == 3))
		return (0);
	if ((str[tmp->i] == '<' || str[tmp->i] == '>') && !tmp->check_redir &&
		!tmp->d_qu && !tmp->s_qu)
		return (0);
	if (str[tmp->i] == 0)
		return (0);
	ft_only_dollar(str, tmp);
	return (1);
}

static char	*ft_realloc_aux_one(char *s, t_test *t, char *res)
{
	while (s[++t->i] != '\0')
	{
		if (!ft_aux_loop_two(s, t))
			break ;
		if (s[t->i] == '$' && (s[t->i + 1] != ' ' &&
			s[t->i + 1] != '\0') && !t->s_qu && !t->one_dollar)
		{
			while (s[t->i] == '$')
				res = ft_realloc_var(s, res, t);
			if (s[t->i] == 0)
				break ;
		}
		ft_aux_loop_quotes(s, t);
		if (s[t->i] == 92)
			t->i++;
		if (s[t->i] != 0)
		{
			t->aux = ft_join_char(res, s[t->i]);
			free(res);
			res = t->aux;
		}
	}
	return (res);
}

char		*ft_realloc_str(t_test *tmp, char *str, int i, int cut)
{
	char	*res;
	char	*aux;

	tmp->d_qu = 0;
	tmp->s_qu = 0;
	tmp->cut = cut;
	tmp->i = i;
	tmp->key = 0;
	tmp->one_dollar = 0;
	tmp->check_redir = 0;
	aux = ft_strdup("");
	res = ft_realloc_aux_one(str, tmp, aux);
	if ((tmp->d_qu || tmp->s_qu) && cut == 13)
	{
		free(res);
		res = NULL;
	}
	tmp->cut = 0;
	return (res);
}
