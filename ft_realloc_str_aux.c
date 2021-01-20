/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_str_aux.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 11:02:40 by fjimenez          #+#    #+#             */
/*   Updated: 2021/01/13 18:15:12 by fjimenez         ###   ########.fr       */
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

void		ft_realloc_aux_two(char *str, t_test *tmp)
{
	ft_aux_loop_quotes(str, tmp);
	if (tmp->one_dollar)
		tmp->one_dollar = 0;
	if (tmp->check_redir)
		tmp->check_redir = 0;
	if (str[tmp->i] == 92 && (!tmp->d_qu && !tmp->s_qu))
	{
		if (str[tmp->i + 1] == '$' || str[tmp->i + 1] == '<' ||
			str[tmp->i + 1] == '>' || str[tmp->i + 1] == ' ' ||
			str[tmp->i + 1] == ';' || str[tmp->i + 1] == '|')
			tmp->i++;
		if (str[tmp->i] == '$')
			tmp->one_dollar = 1;
		if (str[tmp->i] == '<' || str[tmp->i] == '>')
			tmp->check_redir = 1;
	}
	else if (str[tmp->i] == ' ' && (!tmp->d_qu && !tmp->s_qu))
	{
		while (ft_isspace(str[tmp->i]))
			tmp->i++;
		tmp->i--;
	}
}
