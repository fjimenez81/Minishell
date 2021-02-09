/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 17:14:03 by fjimenez          #+#    #+#             */
/*   Updated: 2021/02/08 20:11:50 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_inc_cont(char *s, char *res, t_test *t)
{
	t->i += (!ft_strcmp(res, "") && s[t->i + 1] == ' ') ?
		1 : ft_strlen(t->dollar) - 1;
	t->i -= t->ck_key > 0 ? t->ck_key - 2 : 0;
	if (t->dollar[ft_strlen(t->dollar) - 1] == '=')
		t->i -= 1;
	t->i++;
	free(t->dollar);
	ft_aux_loop_quotes(s, t);
}

static void	ft_only_dollar(char *s, t_test *t)
{
	if (s[t->i] == '$' && (s[t->i + 1] == 34 || s[t->i + 1] == 39 ||
		s[t->i + 1] == 92))
	{
		if (s[t->i + 1] == 34 && !t->d_qu && !t->s_qu)
		{
			t->d_qu = 1;
			t->i += 2;
		}
		if (s[t->i + 1] == 39 && !t->s_qu)
		{
			t->s_qu = 1;
			t->i += 2;
		}
		if ((s[t->i + 1] == 39 && t->d_qu) ||
			s[t->i + 1] == 92)
			t->one_dollar = 1;
	}
}

static int	ft_aux_loop_two(char *s, t_test *t)
{
	ft_realloc_aux_two(s, t);
	if (((s[t->i] == ' ' || s[t->i] == '<' || s[t->i] == '>') &&
		!t->check_redir && !t->d_qu && !t->s_qu &&
		t->cut == 2) || (s[t->i] == '=' && t->cut == 3))
		return (0);
	if ((s[t->i] == '<' || s[t->i] == '>') && !t->check_redir &&
		!t->d_qu && !t->s_qu && !t->cut)
		{
			return (0);
		}
	if (s[t->i] == 0)
		return (0);
	ft_only_dollar(s, t);
	if (s[t->i] == '=' && s[t->i + 1] == '~' &&
		!t->d_qu && !t->s_qu && !t->tilde)
		t->tilde = 1;
	return (1);
}

static char	*ft_realloc_aux_one(char *s, t_test *t, char *res)
{
	while (s[++t->i] != '\0')
	{
		if (((s[t->i] == '~' && !t->i) || t->tilde == 1) &&
			(s[t->i + 1] == '/' || s[t->i + 1] == 0 || s[t->i + 1] == '='))
			res = ft_tilde_redir(t, res);
		if (!ft_aux_loop_two(s, t))
			break ;
		if (s[t->i] == '$' && (s[t->i + 1] != ' ' &&
			s[t->i + 1] != '\0') && !t->s_qu && !t->one_dollar && t->cut != 4)
		{
			while (s[t->i] == '$')
				res = ft_realloc_var(s, res, t);
			if (s[t->i] == 0 || t->bool == 4)
				break ;
		}
		if (s[t->i] == 92 && !t->slash)
			t->i++;
		if (s[t->i] != 0)
		{
			t->aux = ft_join_char(res, s[t->i]);
			free(res);
			res = t->aux;
		}
	}
	return (res);
}

char		*ft_realloc_str(char *str, int i, int cut)
{
	char	*res;
	char	*aux;
	t_test	tmp;

	ft_bzero(&tmp, sizeof(t_test));
	tmp.cut = cut;
	tmp.i = i;
	tmp.status = g_status;
	aux = ft_strdup("");
	res = ft_realloc_aux_one(str, &tmp, aux);
	if (tmp.bool == 4 && cut != 13)
		ft_print_error(res, NULL, ": bad substitution");
	if (((tmp.d_qu || tmp.s_qu) && cut == 13) || (cut != 13 && tmp.bool == 4))
	{
		free(res);
		res = NULL;
	}
	return (res);
}
