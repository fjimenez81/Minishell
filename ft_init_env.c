/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 13:52:05 by fernando          #+#    #+#             */
/*   Updated: 2021/02/08 21:40:39 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_change_dollar(t_shell *p, t_dup *redirs, int n)
{
	int		i;
	char	*aux;

	p->n = n;
	p->upper = ft_split_cmd(p->pipesplit[n], ' ');
	if (redirs->bool_in || redirs->bool_out || redirs->bool)
	{
		ft_free_tab(p->cmp);
		p->cmp = ft_split_cmd(p->pipesplit[p->n], ' ');
	}
	i = -1;
	while (p->cmp[++i])
	{
		aux = ft_realloc_str(p->cmp[i], -1, 0);
		free(p->cmp[i]);
		p->cmp[i] = aux;
		if (p->cmp[i] == NULL)
			p->ret = 1;
	}
	p->args = ft_len_tab(p->cmp);
	ft_lst_cmd(p->cmp[p->args - 1]);
}

void	ft_lst_cmd(char *s)
{
	int		i;
	char	*tmp;

	i = -1;
	while (g_envp[++i])
	{
		if (g_envp[i][0] == '_' && g_envp[i][1] == '=')
		{
			tmp = ft_strjoin("_=", s);
			free(g_envp[i]);
			g_envp[i] = tmp;
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
