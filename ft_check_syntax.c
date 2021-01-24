/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:43:31 by fjimenez          #+#    #+#             */
/*   Updated: 2021/01/23 17:34:46 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_print_syntax_aux_two(t_test *t)
{
	t->i++;
	if (t->aux[t->i] == ' ')
	{
		while (t->aux[t->i] == ' ')
			t->i++;
		if (t->aux[t->i] == '>')
		{
			ft_putstr_fd("\033[1;31m[Minishell]: ", 1);
			ft_putendl_fd("syntax error near unexpected token `>'", 1);
			free(t->aux);
			return (0);
		}
	}
	if (t->aux[t->i] == '<')
	{
		ft_putstr_fd("\033[1;31m[Minishell]: ", 1);
		ft_putendl_fd("syntax error near unexpected token `<'", 1);
		free(t->aux);
		return (0);
	}
	t->i--;
	return (1);
}

static int	ft_print_syntax_aux(t_test *t)
{
	if ((t->aux[t->i] == '<' || t->aux[t->i] == '>') && !t->s_qu && !t->d_qu)
	{
		if (t->aux[t->i] == '>')
			if (!ft_print_syntax_aux_two(t))
				return (0);
		if (t->aux[t->i + 1] == 0)
		{
			ft_putstr_fd("\033[1;31m[Minishell]: ", 1);
			ft_putendl_fd("syntax error near unexpected token `newline'", 1);
			free(t->aux);
			return (0);
		}
	}
	return (1);
}

static int	ft_print_syntax_three(t_test *t)
{
	if ((t->aux[t->i] == '|' && t->aux[t->i + 1] == ';') ||
			t->aux[0] == '|')
	{
		ft_putstr_fd("\033[1;31m[Minishell]: ", 1);
		ft_putendl_fd("syntax error near unexpected token `|'", 1);
		free(t->aux);
		return (0);
	}
	if ((t->aux[t->i] == ';' && t->aux[t->i + 1] == '|') ||
			t->aux[0] == ';')
	{
		ft_putstr_fd("\033[1;31m[Minishell]: ", 1);
		ft_putendl_fd("syntax error near unexpected token `;'", 1);
		free(t->aux);
		return (0);
	}
	return (1);
}

static int	ft_print_syntax_two(t_test *t)
{
	if (t->aux[t->i + 1] == ' ')
	{
		while (t->aux[++t->i])
		{
			if (t->aux[t->i] != ' ' && t->aux[t->i] != '<' &&
				t->aux[t->i] != '>')
				break ;
		}
		if (t->aux[t->i] == ';')
			t->aux[0] = ';';
		else if (t->aux[t->i] == '|')
			t->aux[0] = '|';
	}
	if (t->aux[t->i] == '|' && t->aux[t->i + 1] == '|')
	{
		ft_putstr_fd("\033[1;31m[Minishell]: ", 1);
		ft_putendl_fd("syntax error near unexpected token `||'", 1);
		free(t->aux);
		return (0);
	}
	if (!ft_print_syntax_three(t))
		return (0);
	return (1);
}

int			ft_print_syntax(t_test *t)
{
	if (!ft_print_syntax_aux(t))
		return (0);
	if (t->aux[t->i] == 92 && t->aux[t->i + 1] == 92)
		t->i += 2;
	if (t->aux[t->i] == 92 && (t->aux[t->i + 1] == ';' ||
			t->aux[t->i + 1] == '|'))
		t->i += 2;
	if (t->aux[t->i] == ';' && t->aux[t->i + 1] == ';' &&
			!t->d_qu && !t->s_qu)
	{
		ft_putstr_fd("\033[1;31m[Minishell]: ", 1);
		ft_putendl_fd("syntax error near unexpected token `;;'", 1);
		free(t->aux);
		return (0);
	}
	if ((t->aux[t->i] == ';' || t->aux[t->i] == '|') && !t->d_qu && !t->s_qu)
		if (!ft_print_syntax_two(t))
			return (0);
	return (1);
}
