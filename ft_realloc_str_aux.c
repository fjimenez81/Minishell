/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_str_aux.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 11:02:40 by fjimenez          #+#    #+#             */
/*   Updated: 2020/12/12 14:54:54 by fjimenez         ###   ########.fr       */
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

static void	ft_aux_loop(char *str, t_test *tmp)
{
	if (str[tmp->i] == '\"' && str[tmp->i - 1] != '\\' &&
		tmp->d_qu == 0 && tmp->s_qu == 0)
	{
		tmp->i += 1;
		tmp->d_qu = 1;
	}
	else if (str[tmp->i] == '\"' && str[tmp->i - 1] != '\\' && tmp->d_qu == 1)
	{
		tmp->i += 1;
		tmp->d_qu = 0;
	}
	if (str[tmp->i] == '\'' && str[tmp->i - 1] != '\\' &&
		tmp->s_qu == 0 && tmp->d_qu == 0)
	{
		tmp->i += 1;
		tmp->s_qu = 1;
	}
	else if (str[tmp->i] == '\'' && str[tmp->i - 1] != '\\' && tmp->s_qu == 1)
	{
		tmp->i += 1;
		tmp->s_qu = 0;
	}
}

void		ft_realloc_aux_two(char *str, t_test *tmp)
{
	ft_aux_loop(str, tmp);
	if (str[tmp->i] == '\\' && (str[tmp->i + 1] == '\'' ||
		str[tmp->i + 1] == '\"'))
		tmp->i += 1;
	else if (str[tmp->i] == '\\' && str[tmp->i + 1] == ' ' &&
		(tmp->d_qu == 1 || tmp->s_qu == 1))
		tmp->i += 1;
	else if (str[tmp->i] == '\\' && (tmp->d_qu == 0 && tmp->s_qu == 0))
		tmp->i += 1;
	else if (str[tmp->i] == '\\' && str[tmp->i + 1] == '\\' &&
		(tmp->d_qu == 0 && tmp->s_qu == 0))
		tmp->i += 1;
	else if (str[tmp->i] == ' ' && str[tmp->i - 1] != '\\' &&
		str[tmp->i + 1] == ' ' && (tmp->d_qu == 0 && tmp->s_qu == 0))
	{
		while (ft_isspace(str[tmp->i]))
			tmp->i += 1;
		tmp->i -= 1;
	}
}
