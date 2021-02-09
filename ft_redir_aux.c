/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 15:53:45 by fjimenez          #+#    #+#             */
/*   Updated: 2021/02/09 16:31:41 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cut_redit_in(t_test *t, t_dup *redirs, char *s)
{
	t->j = t->i;
	t->i++;
	if (!ft_open_redir_in(redirs, s, t))
		return (0);
	t->k = t->i + 1;
	while (s[t->k] != ' ' && s[t->k] != 0)
		t->k++;
	t->k++;
	while (t->j < t->k)
	{
		s[t->j] = ' ';
		t->j++;
	}
	return (1);
}

int	ft_cut_redir_out(t_test *t, t_dup *redirs, char *s)
{
	t->j = t->i;
	if (!ft_redir_check_out(redirs, s, t))
		return (0);
	t->k = t->i + 1;
	while (s[t->k] != ' ' && s[t->k] != 0)
		t->k++;
	t->k++;
	while (t->j < t->k)
	{
		s[t->j] = ' ';
		t->j++;
	}
	return (1);
}

int	ft_redir_out_aux(char *s, t_dup *redirs, t_test *tst)
{
	tst->k = tst->i;
	redirs->output = ft_realloc_str(s + tst->i, -1, 2);
	if (!ft_strcmp(redirs->output, "~") || (ft_strchr(s + tst->k, '$') &&
		!ft_strchr(s + tst->k, 34) &&
		!ft_strchr(s + tst->k, 39)))
	{
		if (ft_strcmp(redirs->output, "~"))
		{
			tst->aux = ft_realloc_str(s, tst->k - 1, 4);
			ft_print_error(tst->aux, NULL, ": ambiguous redirect");
		}
		else
		{
			tst->aux = ft_get_var("HOME=", 0);
			ft_print_error(tst->aux, NULL, ": Is a directory");
		}
		free(tst->aux);
		free(redirs->output);
		g_status = 1;
		return (0);
	}
	return (1);
}

int	ft_redir_in_aux(char *s, t_dup *redirs, t_test *tst)
{
	tst->k = tst->i;
	redirs->input = ft_realloc_str(s + tst->i, -1, 2);
	if (!ft_strcmp(redirs->input, "~") || (ft_strchr(s + tst->k, '$') &&
		!ft_strchr(s + tst->k, 34) &&
		!ft_strchr(s + tst->k, 39)))
	{
		if (ft_strcmp(redirs->input, "~"))
		{
			tst->aux = ft_realloc_str(s, tst->k - 1, 4);
			ft_print_error(tst->aux, NULL, ": ambiguous redirect");
		}
		else
		{
			tst->aux = ft_get_var("HOME=", 0);
			ft_print_error(tst->aux, NULL, ": Is a directory");
		}
		free(tst->aux);
		free(redirs->input);
		g_status = 1;
		return (0);
	}
	return (1);
}
