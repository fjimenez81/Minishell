/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <fjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 10:55:30 by fjimenez          #+#    #+#             */
/*   Updated: 2020/09/14 13:25:02 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_loop_caracter(char *vars)
{
	int bool;

	bool = 0;
	while (*vars)
	{
		if (*vars == '{' &&  *(vars - 1) == '$')
		{
			bool = 1;
			vars++;
		}
		if (*vars == '?' && bool == 1)
			vars++;
		if (*vars == '}' && bool == 1)
			vars++;
		if (((*vars == '\"'|| *vars == '\'') && *(vars - 1) != '\\') ||
			(*vars == '\\' && *(vars + 1) != '\\') || (*vars == '?' &&
			*(vars - 1) == '$'))
			vars++;
		if (*vars == '=')
			break ;
		if (!ft_isalpha(*vars) && !ft_isalnum(*vars) && !ft_isdigit(*vars) &&
			*vars != '_')
			return (0);
		vars++;
	}
	return (1);
}

static void	ft_valid_args(t_test *tst, int *bool)
{
	int j;
	int k;

	j = 0;
	while (tst->var_exp[++j])
	{
		k = -1;
		while (tst->var_exp[j][++k])
		{
			if (((!ft_isalpha(tst->var_exp[j][k]) && k == 0) ||
				(tst->var_exp[j][k] == '\\' &&
				tst->var_exp[j][k + 1] == '\\') ||
				tst->var_exp[j][k] == ' ') && *bool == 0)
			{
				ft_putstr_fd("\033[1;31m", 1);
				ft_putstr_fd("export : not an identifier: ", 1);
				ft_putendl_fd(ft_realloc_str(tst, tst->var_exp[j], -1, 3), 1);
				*bool = 1;
				break ;
			}
		}
	}	
}

static int	ft_check_var(char *vars)
{
	if ((!ft_isalpha_cm(vars[0]) && vars[0] != '_') ||
		(vars[0] == '\\' && vars[1] == '\\'))
		return (0);
	if (!ft_loop_caracter(vars + 1))
		return (0);
	return (1);
}

void		ft_check_var_loop(t_test *tst)
{
	int i;
	int bool;

	i = 0;
	bool = 0;
	while (tst->var_exp[++i])
	{
		if (!ft_check_var(tst->var_exp[i]))
		{
			ft_valid_args(tst, &bool);
			ft_memmove(tst->var_exp[i], "", ft_strlen(tst->var_exp[i]));
		}
	}
}