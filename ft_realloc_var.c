/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 10:59:34 by fjimenez          #+#    #+#             */
/*   Updated: 2020/10/07 20:43:08 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_keys_loop(t_test *tmp, int i)
{
	char *aux;

	i = -1;
	while (tmp->dollar[++i] != '}')
	{
		if (tmp->dollar[i] == '{')
			i++;
		aux = ft_join_char(tmp->c_keys, tmp->dollar[i]);
		tmp->c_keys = aux;
		free(aux);
	}
}

static char	*ft_check_keys(t_test *tmp)
{
	int i;
	int bool;

	i = -1;
	bool = 0;
	while (tmp->dollar[++i])
	{
		if (tmp->dollar[i] == '{' && bool == 0 && i == 1)
			bool = 1;
		if (tmp->dollar[i] == '}' && bool == 1)
			tmp->ck_key = 1;
		if (tmp->ck_key > 0)
			tmp->ck_key += 1;
	}
	if (tmp->ck_key > 0)
		ft_keys_loop(tmp, i);
	return (tmp->c_keys);
}

static char	*ft_dollar_aux(t_test *tmp, char *res)
{
	char *var;

	tmp->c_keys = tmp->ck_key > 0 ?
		ft_strjoin(ft_strrchr(tmp->c_keys, '$') + 1, "=") :
		ft_strjoin(ft_strrchr(tmp->dollar, '$') + 1, "=");
	var = ft_print_var(tmp->c_keys);
	res = ft_strjoin(res, var);
	free(tmp->c_keys);
	return (res);
}

char		*ft_realloc_var(char *str, char *res, t_test *tmp)
{
	char *var;

	tmp->ck_key = 0;
	tmp->c_keys = "\0";
	tmp->dollar = ft_cut_end(str + tmp->i, 0);
	tmp->c_keys = ft_check_keys(tmp);
	if (tmp->c_keys[1] == '?' || tmp->dollar[1] == '?')
	{
		var = ft_itoa(WEXITSTATUS(tmp->status));
		res = ft_strjoin(res, var);
		free(var);
	}
	else
		res = ft_dollar_aux(tmp, res);
	tmp->i += (!ft_strcmp(var, "") && str[tmp->i + 1] == ' ') ?
		1 : ft_strlen(tmp->dollar) - 1;
	tmp->i -= tmp->ck_key > 0 ? tmp->ck_key - 2 : 0;
	free(tmp->dollar);
	return (res);
}
