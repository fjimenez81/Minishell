/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 13:52:05 by fernando          #+#    #+#             */
/*   Updated: 2021/01/11 16:45:13 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_wordlen_aux(char *s, int *count)
{
	if (*s == '\"')
	{
		*count += 1;
		s++;
		while (*s && *s != '\"')
		{
			*count += 1;
			s++;
		}
	}
	if (*s == '\'')
	{
		*count += 1;
		s++;
		while (*s && *s != '\'')
		{
			*count += 1;
			s++;
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
