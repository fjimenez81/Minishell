/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 10:59:34 by fjimenez          #+#    #+#             */
/*   Updated: 2021/01/23 15:59:22 by fjimenez         ###   ########.fr       */
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
	int bool;

	i = -1;
	bool = 0;
	while (t->dollar[++i])
	{
		if (t->dollar[i] == '{' && bool == 0 && i == 1)
			bool = 1;
		if (t->dollar[i] == '}' && bool == 1)
			t->ck_key = 1;
		if (t->ck_key > 0)
			t->ck_key += 1;
	}
	if (t->ck_key > 0)
		ft_keys_loop(t, i);
	return (t->c_keys);
}

static char	*ft_dollar_aux(t_test *tmp, char *res)
{
	char *var;
	char *aux;

	free(tmp->c_keys);
	tmp->c_keys = tmp->ck_key > 0 ?
		ft_strjoin(ft_strrchr(tmp->c_keys, '$') + 1, "=") :
		ft_strdup(ft_strrchr(tmp->dollar, '$') + 1);
	var = ft_print_var(tmp->c_keys);
	if (!tmp->d_qu)
		while (*var == ' ')
			var++;
	aux = ft_strjoin(res, var);
	free(res);
	res = aux;
	free(tmp->c_keys);
	return (res);
}

static void	ft_aux_var(char *str, t_test *tmp)
{
	tmp->ck_key = 0;
	tmp->c_keys = ft_strdup("");
	tmp->dollar = ft_cut_end(str + tmp->i, 2);
	tmp->c_keys = ft_check_keys(tmp);
}

char		*ft_realloc_var(char *s, char *res, t_test *t)
{
	char *var;
	char *aux;

	ft_aux_var(s, t);
	if (t->c_keys[1] == '?' || t->dollar[1] == '?')
	{
		if (t->cut == 9)
			var = ft_itoa(1);
		else if (t->cut > 129)
			var = ft_itoa(g_minish->exit);
		else
			var = ft_itoa(WEXITSTATUS(t->status));
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
