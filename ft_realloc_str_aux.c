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

void		ft_aux_loop_quotes(char *str, t_test *tmp)
{
	if (str[tmp->i] == 34 && !tmp->d_qu && !tmp->s_qu)
	{
		tmp->i++;
		tmp->d_qu = 1;
	}
	if (str[tmp->i] == 34 && tmp->d_qu)
	{
		tmp->i++;
		tmp->d_qu = 0;
	}
	if (str[tmp->i] == 39 && !tmp->s_qu && !tmp->d_qu)
	{
		tmp->i++;
		tmp->s_qu = 1;
	}
	if (str[tmp->i] == 39 && tmp->s_qu)
	{
		tmp->i++;
		tmp->s_qu = 0;
	}
}

static void	ft_aux_loop(char *str, t_test *tmp)
{
	ft_aux_loop_quotes(str, tmp);
	if (tmp->one_dollar)
		tmp->one_dollar = 0;
	if (tmp->check_redir)
		tmp->check_redir = 0;
	if (str[tmp->i] == 92 && (str[tmp->i + 1] == 39 || str[tmp->i + 1] == 34))
		tmp->i++;
}

void		ft_realloc_aux_two(char *str, t_test *tmp)
{
	ft_aux_loop(str, tmp);
	if (str[tmp->i] == 92 && (!tmp->d_qu && !tmp->s_qu))
	{
		tmp->i++;
		if (str[tmp->i] == '$')
			tmp->one_dollar = 1;
		if (str[tmp->i] == '<' || str[tmp->i] == '>')
			tmp->check_redir = 1;
	}
	else if (str[tmp->i] == 92 && (tmp->d_qu || tmp->s_qu))
	{
		if (str[tmp->i + 1] == 92)
			tmp->i++;
	}
	else if (str[tmp->i] == ' ' && (!tmp->d_qu && !tmp->s_qu))
	{
		while (ft_isspace(str[tmp->i]))
			tmp->i++;
		tmp->i--;
	}
}
