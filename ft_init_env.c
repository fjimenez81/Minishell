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

void	ft_getcount_aux(char **s, int c)
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
	if (**s == 92 && **(s + 1) == 92)
		*s += 1;
	else if (**s == 92 && **(s + 1) == c)
		*s += 1;
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
