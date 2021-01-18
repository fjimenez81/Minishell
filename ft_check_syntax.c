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

void		ft_syntax_quotes(t_test *t, char *line)
{
	if (line[t->i] == '\"' && line[t->i - 1] != 92 && !t->d_qu)
	{
		t->d_qu = 1;
		t->i += 1;
	}
	if (line[t->i] == '\'' && line[t->i - 1] != 92 && !t->s_qu)
	{
		t->s_qu = 1;
		t->i += 1;
	}
	if (line[t->i] == '\"' && line[t->i - 1] != 92 && t->d_qu)
	{
		t->d_qu = 0;
		t->i += 1;
	}
	if (line[t->i] == '\'' && line[t->i - 1] != 92 && t->s_qu)
	{
		t->s_qu = 0;
		t->i += 1;
	}
}

static int	ft_print_syntax_aux_two(t_test *t, char *line)
{
	if (((line[t->i] == ' ' || line[t->i] == ';') && t->i == 0) ||
		(line[t->i] == ' ' && line[t->i - 1] == ';'))
	{
		while(ft_isspace(line[t->i]))
			t->i += 1;
		if (line[t->i] == ';' && line[t->i + 1] != ';')
		{
			ft_putstr_fd("\033[1;31m[Minishell]: ", 1);
			ft_putendl_fd("syntax error near unexpected token `;'", 1);
			return (0);
		}
	}
	return (1);
}

static int	ft_print_syntax_aux(t_test *t, char *line)
{
	if (!ft_print_syntax_aux_two(t, line))
		return (0);
	if (line[t->i] == 92 && line[t->i + 1] == 92)
		t->i += 1;
	else if (line[t->i] == 92 && line[t->i + 1] == ';')
		t->i += 1;
	else if (line[t->i] == ';' && line[t->i + 1] == ';' && !t->d_qu && !t->s_qu)
	{
		ft_putstr_fd("\033[1;31m[Minishell]: ", 1);
		ft_putendl_fd("syntax error near unexpected token `;;'", 1);
		return (0);
	}
	return (1);
}

int			ft_print_syntax(t_test *t, char *line)
{
	if (!ft_print_syntax_aux(t, line))
		return (0);
	if (line[t->i - 2] != 92 && ((line[t->i - 1] == ';' &&
		line[t->i] == '|') || (line[t->i - 1] == '|' &&
		line[t->i] == ';') || (line[t->i - 1] == '|' &&
		line[t->i] == '|')) && !t->d_qu && !t->s_qu)
	{
		ft_putstr_fd("\033[1;31m[Minishell]: ", 1);
		ft_putstr_fd("syntax error near unexpected token ", 1);
		if (line[t->i - 1] == '|' && line[t->i] == '|')
			ft_putendl_fd("`||'", 1);
		else if (line[t->i - 1] == ';')
			ft_putendl_fd("`;'", 1);
		else if (line[t->i - 1] == '|')
			ft_putendl_fd("`|'", 1);
		return (0);
	}
	return (1);
}
