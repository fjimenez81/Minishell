/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 13:52:05 by fernando          #+#    #+#             */
/*   Updated: 2021/01/13 18:15:34 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_all(t_test *t, t_shell *pcs)
{
	ft_free_tab(pcs->cmp);
	ft_free_tab(t->cmd);
	free(t->line);
	free(pcs);
}

void	ft_redir_quotes(t_test *tst, t_shell *pcs)
{
	if (tst->check_redir)
		tst->check_redir = 0;
	if ((pcs->redir[tst->i] == 34 || pcs->redir[tst->i] == 39) && !pcs->quotes)
		pcs->quotes = 1;
	else if ((pcs->redir[tst->i] == 34 || pcs->redir[tst->i] == 39) &&
			pcs->quotes)
		pcs->quotes = 0;
	else if (pcs->redir[tst->i] == 92)
	{
		tst->i++;
		if ((pcs->redir[tst->i] == '>' || pcs->redir[tst->i] == '<') &&
			!pcs->quotes)
			tst->check_redir = 1;
	}
}

void	ft_getcount_aux(char **s)
{
	if (**s == '\"')
	{
		*s += 1;
		while (**s && **s != '\"')
			*s += 1;
	}
	if (**s == '\'')
	{
		*s += 1;
		while (**s && **s != '\'')
			*s += 1;
	}
}

void	ft_wordlen_aux(char **s, int *count)
{
	if (**s == '\"')
	{
		*count += 1;
		*s += 1;
		while (**s && **s != '\"')
		{
			*s += 1;
			*count += 1;
		}
	}
	if (**s == '\'')
	{
		*s += 1;
		*count += 1;
		while (**s && **s != '\'')
		{
			*s += 1;
			*count += 1;
		}
	}
}

void	init_env(char **env)
{
	int		i;

	if (!(g_envp = (char **)malloc(sizeof(char*) * (ft_len_tab(env) + 1))))
		return ;
	i = -1;
	while (env[++i])
		g_envp[i] = ft_strdup(env[i]);
	g_envp[i] = NULL;
	return ;
}
