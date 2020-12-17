/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 17:14:03 by fjimenez          #+#    #+#             */
/*   Updated: 2020/12/17 09:29:47 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_aux_loop_two(char *str, t_test *tmp)
{
	if (((str[tmp->i] == ' ' || str[tmp->i] == '<' || str[tmp->i] == '>') &&
		str[tmp->i - 1] != '\\' && !tmp->d_qu && !tmp->s_qu &&
		tmp->cut == 2) || (str[tmp->i] == '=' && tmp->cut == 3) ||
		tmp->key == 2)
		return (0);
	if ((str[tmp->i] == '<' || str[tmp->i] == '>' ||
		(str[tmp->i] == ' ' && str[tmp->i + 1] == '>')) &&
		str[tmp->i - 1] != '\\' && !tmp->d_qu && !tmp->s_qu &&
		tmp->cut == 1)
		return (0);
	return (1);
}

static void	ft_only_dollar(char *str, t_test *tmp)
{
	if (str[tmp->i] == '$' && (str[tmp->i + 1] == '\"' ||
		str[tmp->i + 1] == '\'' || str[tmp->i + 1] == '\\'))
	{
		if (str[tmp->i + 1] == '\'' && !tmp->d_qu)
			tmp->s_qu = 1;
		if (!tmp->d_qu)
			tmp->i += 2;
		if (str[tmp->i + 1] == '\'' && tmp->d_qu)
			tmp->one_dollar = 1;
	}
}

static char	*ft_realloc_aux_one(char *str, t_test *tmp)
{
	char	*res;
	char	*aux;

	res = ft_strdup("");
	while (str[++tmp->i] != '\0')
	{
		ft_realloc_aux_two(str, tmp);
		if (!ft_aux_loop_two(str, tmp))
			break ;
		ft_only_dollar(str, tmp);
		if (str[tmp->i] == '$' && str[tmp->i - 1] != '\\' &&
			(str[tmp->i + 1] != ' ' && str[tmp->i + 1] != '\0') &&
			!tmp->s_qu && !tmp->one_dollar)
		{
			res = ft_realloc_var(str, res, tmp);
			tmp->i++;
		}
		aux = ft_join_char(res, str[tmp->i]);
		free(res);
		res = aux;
	}
	return (res);
}

char		*ft_realloc_str(t_test *tmp, char *str, int i, int cut)
{
	char	*res;

	tmp->d_qu = 0;
	tmp->s_qu = 0;
	tmp->cut = cut;
	tmp->i = i;
	tmp->key = 0;
	tmp->one_dollar = 0;
	res = ft_realloc_aux_one(str, tmp);
	if ((tmp->d_qu || tmp->s_qu) && cut == 13)
	{
		free(res);
		res = NULL;
	}
	tmp->cut = 0;
	return (res);
}
