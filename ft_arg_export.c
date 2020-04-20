/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernando <fernando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 12:33:08 by fernando          #+#    #+#             */
/*   Updated: 2020/04/20 20:52:39 by fernando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_join_env(char **g_envp, char *vars)
{
	int		i;
	size_t len1;
	char **res;

	len1 = ft_len_tab(g_envp);

	if (!(res = (char **)malloc(sizeof(char*) * (len1 + 2))))
		return (NULL);
	i = -1;
	while (g_envp[++i])
		res[i] = ft_strdup(g_envp[i]);
	res[i] = ft_strdup(vars);
	i++;
	res[i] = NULL;
	ft_free_tab(g_envp);
	return (res);
}

int		ft_arg_export(char **vars, int args)
{
	int i;

	i = -1;
	if (args)
	{
		if (vars[1] == NULL || !ft_strchr(vars[1] , '='))
            return (1);
		else if (ft_strchr(vars[1], '='))
		{
			g_envp = ft_join_env(g_envp, vars[1]);
			return (1);
		}
		else
			return (1);
		
	}
	return (-1);
}