/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 10:59:34 by fjimenez          #+#    #+#             */
/*   Updated: 2021/02/09 16:33:57 by fjimenez         ###   ########.fr       */
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
		free(tmp->c_keys);
		tmp->c_keys = aux;
	}
}

static char	*ft_check_keys(t_test *t)
{
	int i;

	i = -1;
	t->bool = 0;
	while (t->dollar[++i])
	{
		if (t->dollar[i] == '{' && t->bool == 0 && i == 1)
			t->bool = 1;
		if ((t->dollar[i] == 34 || t->dollar[i] == 39) && t->bool == 1)
			t->bool = 3;
		else if ((t->dollar[i] == 34 || t->dollar[i] == 39) && t->bool == 3)
			t->bool = 4;
		if (t->dollar[i] == '}' && t->bool == 1)
			t->ck_key = 1;
		if (t->ck_key > 0)
			t->ck_key += 1;
	}
	if (t->ck_key > 0 && t->bool != 4)
		ft_keys_loop(t, i);
	return (t->c_keys);
}

static char	*ft_dollar_aux(t_test *tmp, char *res)
{
	char *var;
	char *aux;
	char *chg;

	free(tmp->c_keys);
	tmp->c_keys = tmp->ck_key > 0 ?
		ft_strjoin(ft_strrchr(tmp->c_keys, '$') + 1, "=") :
		ft_strdup(ft_strrchr(tmp->dollar, '$') + 1);
	var = ft_strdup(ft_print_var(tmp->c_keys));
	if (!tmp->d_qu && !tmp->cheat && (var[0] == ' ' ||
		var[ft_strlen(var) - 1] == ' '))
	{
		chg = ft_strtrim(var, " \t");
		free(var);
		var = chg;
	}
	aux = ft_strjoin(res, var);
	free(res);
	res = aux;
	free(tmp->c_keys);
	free(var);
	return (res);
}

static void	ft_aux_var(char *str, t_test *tmp)
{
	tmp->ck_key = 0;
	tmp->c_keys = ft_strdup("");
	tmp->dollar = ft_cut_end(str + tmp->i, 2);
	tmp->c_keys = ft_check_keys(tmp);
	if (str[tmp->i - 1] != 34)
		tmp->cheat = 1;
}

char		*ft_realloc_var(char *s, char *res, t_test *t)
{
	char *var;
	char *aux;

	ft_aux_var(s, t);
	if (t->bool == 4)
	{
		t->i++;
		free(t->c_keys);
		free(res);
		return (t->dollar);
	}
	if (t->c_keys[1] == '?' || t->dollar[1] == '?')
	{
		var = ft_itoa(t->status);
		aux = ft_strjoin(res, var);
		free(res);
		res = aux;
		free(t->c_keys);
		free(var);
	}
	else
		res = ft_dollar_aux(t, res);
	ft_inc_cont(s, res, t);
	return (res);
}
