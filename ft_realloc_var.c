/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 10:59:34 by fjimenez          #+#    #+#             */
/*   Updated: 2020/12/16 18:37:21 by fjimenez         ###   ########.fr       */
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

	free(tmp->c_keys);
	tmp->c_keys = tmp->ck_key > 0 ?
		ft_strjoin(ft_strrchr(tmp->c_keys, '$') + 1, "=") :
		ft_strjoin(ft_strrchr(tmp->dollar, '$') + 1, "=");
	var = ft_print_var(tmp->c_keys);
	free(res);
	res = ft_strjoin(res, var);
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

char		*ft_realloc_var(char *str, char *res, t_test *tmp)
{
	char *var;

	ft_aux_var(str, tmp);
	if (tmp->c_keys[1] == '?' || tmp->dollar[1] == '?')
	{
		free(tmp->c_keys);
		if (tmp->cut == 9)
			var = ft_itoa(1);
		else if (tmp->cut > 129)
			var = ft_itoa(g_minish->exit);
		else
			var = ft_itoa(WEXITSTATUS(tmp->status));
		free(res);
		res = ft_strjoin(res, var);
		free(var);
	}
	else
		res = ft_dollar_aux(tmp, res);
	tmp->i += (!ft_strcmp(var, "") && str[tmp->i + 1] == ' ') ?
		1 : ft_strlen(tmp->dollar) - 1;
	tmp->i -= tmp->ck_key > 0 ? tmp->ck_key - 2 : 0;
	if (tmp->dollar[ft_strlen(tmp->dollar) - 1] == '=')
		tmp->i -= 1;
	free(tmp->dollar);
	return (res);
}
