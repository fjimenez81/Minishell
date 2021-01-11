/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:43:31 by fjimenez          #+#    #+#             */
/*   Updated: 2021/01/11 18:45:32 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_syntax_quotes(t_test *tst, char *line, int *i)
{
	if (line[*i] == '\"' && line[*i - 1] != 92 && !tst->d_qu)
	{
		tst->d_qu = 1;
		*i += 1;
	}
	if (line[*i] == '\'' && line[*i - 1] != 92 && !tst->s_qu)
	{
		tst->s_qu = 1;
		*i += 1;
	}
	if (line[*i] == '\"' && line[*i - 1] != 92 && tst->d_qu)
	{
		tst->d_qu = 0;
		*i += 1;
	}
	if (line[*i] == '\'' && line[*i - 1] != 92 && tst->s_qu)
	{
		tst->s_qu = 0;
		*i += 1;
	}
}

int		ft_print_syntax_aux(t_test *tst, char *line, int i)
{
	if (line[i] == ';' && i == 0 && line[i + 1] != ';')
	{
		ft_putstr_fd("\033[1;31m[Minishell]: ", 1);
		ft_putendl_fd("syntax error near unexpected token `;'", 1);
		return (0);
	}
	if (line[i - 2] != 92 && line[i - 1] == line[i] && line[i] == ';' &&
		!tst->d_qu && !tst->s_qu)
	{
		ft_putstr_fd("\033[1;31m[Minishell]: ", 1);
		ft_putendl_fd("syntax error near unexpected token `;;'", 1);
		return (0);
	}
	return (1);
}

int		ft_print_syntax(t_test *tst, char *line, int i)
{
	if (!ft_print_syntax_aux(tst, line, i))
		return (0);
	if (line[i - 2] != 92 && ((line[i - 1] == ';' && line[i] == '|') ||
		(line[i - 1] == '|' && line[i] == ';') ||
		(line[i - 1] == '|' && line[i] == '|')) && !tst->d_qu && !tst->s_qu)
	{
		ft_putstr_fd("\033[1;31m[Minishell]: ", 1);
		ft_putstr_fd("syntax error near unexpected token ", 1);
		if (line[i - 1] == '|' && line[i] == '|')
			ft_putendl_fd("`||'", 1);
		else if (line[i - 1] == ';')
			ft_putendl_fd("`;'", 1);
		else if (line[i - 1] == '|')
			ft_putendl_fd("`|'", 1);
		return (0);
	}
	return (1);
}
