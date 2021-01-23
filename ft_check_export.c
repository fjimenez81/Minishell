/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 10:55:30 by fjimenez          #+#    #+#             */
/*   Updated: 2021/01/23 16:01:22 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_loop_caracter(t_test *t, char *s)
{
	while (s[++t->i])
	{
		ft_aux_loop_quotes(s, t);
		if (s[t->i] == '$' && s[t->i + 1] == '{' && !t->d_qu && !t->s_qu)
		{
			t->i++;
			while (s[t->i] != '}')
				t->i++;
			t->i++;
		}
		if (s[t->i] == 92)
			t->i++;
		if (s[t->i] == '$' && s[t->i + 1] == '?')
			t->i += 2;
		if (s[t->i] == '=' && !t->d_qu && !t->s_qu)
			break ;
		if (!ft_isalnum(s[t->i]))
			return (0);
	}
	return (1);
}

static int	ft_check_var(t_test *t, char *vars)
{
	t->i = -1;
	t->d_qu = 0;
	t->s_qu = 0;
	if ((!ft_isalpha_cm(vars[0]) && vars[0] != '_') ||
		(vars[0] == '\\' && vars[1] == '\\'))
		return (0);
	if (!ft_loop_caracter(t, vars + 1))
		return (0);
	return (1);
}

void		ft_check_var_loop(t_test *t)
{
	int		i;
	char	*aux;

	i = 0;
	while (t->var_exp[++i])
	{
		if (!ft_check_var(t, t->var_exp[i]))
		{
			aux = ft_realloc_str(t, t->var_exp[i], -1, 0);
			ft_putstr_fd("\033[1;31m[Minishell]: export: `", 1);
			ft_putstr_fd(aux, 1);
			ft_putendl_fd("\': not a valid identifier", 1);
			free(aux);
			t->status = 1;
			ft_memmove(t->var_exp[i], "", ft_strlen(t->var_exp[i]));
		}
	}
}
