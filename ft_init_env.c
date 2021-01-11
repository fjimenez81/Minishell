/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 13:52:05 by fernando          #+#    #+#             */
/*   Updated: 2021/01/11 11:13:13 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_print_syntax(char *line, int i)
{
	if ((line[i - 1] == ';' && line[i] == '|') ||
		(line[i - 1] == '|' && line[i] == ';') ||
		(line[i - 1] == '|' && line[i] == '|'))
	{
		ft_putstr_fd("\033[1;31m[Minishell]: ", 1);
		ft_putstr_fd("syntax error near unexpected token ", 1);
		if (line[i - 1] == '|' && line[i] == '|')
			ft_putendl_fd("`||'", 1);
		else if (line[i - 1] == ';')
			ft_putendl_fd("`;'", 1);
		else if (line[i - 1] == '|')
			ft_putendl_fd("`|'", 1);
		return (0);
	}
	return (1);
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
