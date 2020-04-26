/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernando <fernando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 13:52:05 by fernando          #+#    #+#             */
/*   Updated: 2020/04/24 21:00:38 by fernando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
