/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 15:13:48 by fjimenez          #+#    #+#             */
/*   Updated: 2021/02/08 21:39:03 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_open_redir_out(t_dup *redirs, char *s, int flags, t_test *t)
{
	while (ft_isspace(s[t->i]))
		t->i += 1;
	if (!ft_redir_out_aux(s, redirs, t))
		return (0);
	if ((redirs->out = open(redirs->output, flags, 0644)) == -1)
	{
		ft_print_error(redirs->output, NULL, ": No such file or directory");
		free(redirs->output);
		g_status = 1;
		return (0);
	}
	if (s[t->i] == '>')
		t->i--;
	if (redirs->bool)
		redirs->out = 0;
	redirs->bool_out = 1;
	free(redirs->output);
	return (1);
}

// static void	ft_redir_cut(t_dup *redirs, char *s, int i)
// {
// 	if (!redirs->cut)
// 	{
// 		redirs->cut = i;
// 		while (ft_isspace(s[redirs->cut]))
// 			redirs->cut--;
// 		redirs->cut++;
// 	}
// }

int			ft_open_redir_in(t_dup *redirs, char *s, t_test *t)
{
	//ft_redir_cut(redirs, s, t->i - 2);
	while (ft_isspace(s[t->i]))
		t->i += 1;
	if (!ft_redir_in_aux(s, redirs, t))
		return (0);
	if (redirs->in > 0)
		close(redirs->in);
	if ((redirs->in = open(redirs->input, O_RDONLY)) == -1)
	{
		ft_print_error(redirs->input, NULL, ": No such file or directory");
		free(redirs->input);
		g_status = 1;
		return (0);
	}
	if (s[t->i] == '<')
		t->i--;
	redirs->bool_in = 1;
	free(redirs->input);
	return (1);
}

int	ft_redir_check_out(t_dup *redirs, char *s, t_test *t)
{
	//ft_redir_cut(redirs, s, t->i - 1);
	if (redirs->out > 1)
		close(redirs->out);
	t->i++;
	if (s[t->i] == '>' && s[t->i - 1] == '>')
	{
		t->i++;
		if (!ft_open_redir_out(redirs, s, O_CREAT | O_APPEND | O_RDWR, t))
			return (0);
	}
	else
	{
		if (s[t->i - 1] == '<')
		{
			redirs->bool = 1;
			t->i++;
		}
		if (!ft_open_redir_out(redirs, s, O_CREAT | O_TRUNC | O_RDWR, t))
			return (0);
	}
	return (1);
}

int			ft_check_redir(t_dup *redirs, char *s)
{
	t_test t;

	ft_bzero(&t, sizeof(t_test));
	t.i = -1;
	while (s[++t.i])
	{
		ft_aux_loop_quotes(s, &t);
		if ((s[t.i] == '>' || (s[t.i] == '<' &&
			s[t.i + 1] == '>')) && !t.d_qu && !t.s_qu)
		{
			if (!ft_cut_redir_out(&t, redirs, s))
				return (0);
		}
		else if (s[t.i] == '<' && !t.d_qu && !t.s_qu)
		{
			if (!ft_cut_redit_in(&t, redirs, s))
				return (0);
		}
		if (s[t.i] == 92)
			t.i++;
	}
	if (s[0] == '>' || s[0] == '<')
		return ((g_status = 0));
	return (1);
}
