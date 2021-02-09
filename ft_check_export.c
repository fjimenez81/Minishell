/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 10:55:30 by fjimenez          #+#    #+#             */
/*   Updated: 2021/02/02 11:33:42 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_var(t_test *t)
{
	t->k = -1;
	if (t->aux[0] == '_' && t->aux[1] == '=')
		return (2);
	while (t->aux[++t->k])
	{
		if (t->k == 0 && ft_isdigit(t->aux[t->k]))
			return (0);
		if (t->aux[t->k] == '=')
			break ;
		if (!ft_isalnum(t->aux[t->k]) && t->aux[t->k] != '_')
			return (0);
	}
	return (1);
}

void		ft_check_var_loop(t_shell *pcs, t_test *t, int i)
{
	while (t->var_exp[++i])
	{
		t->aux = ft_realloc_str(t->var_exp[i], -1, 0);
		if (t->aux == NULL)
		{
			t->bool = 1;
			pcs->ret = 1;
			break ;
		}
		if (ft_check_var(t) == 2)
		{
			t->bool = 1;
			free(t->aux);
			break ;
		}
		if (!ft_check_var(t) || !ft_strlen(t->aux) || t->aux[0] == '=')
		{
			ft_print_error(t->aux, "export: `", "\': not a valid identifier");
			pcs->ret = 1;
			ft_memmove(t->var_exp[i], "", ft_strlen(t->var_exp[i]));
		}
		free(t->aux);
	}
}
