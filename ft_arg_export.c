/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernando <fernando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 12:33:08 by fernando          #+#    #+#             */
/*   Updated: 2020/04/21 21:37:04 by fernando         ###   ########.fr       */
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
	int j;
	int len;
	char **tmp;

	
	if (g_bool)
	{
		tmp = g_var;
		len = ft_len_tab(vars) + ft_len_tab(g_var);
		ft_free_tab(g_var);
	}
		
	else
	{
		len = ft_len_tab(vars);
	}

	if (!(g_var = (char**)malloc(sizeof(char*) * (len + 1))))
		return (-1);
	
	
	if (args)
	{
		if (vars[1] == NULL || !ft_strchr(vars[1] , '='))
            return (1);
		else if (ft_strchr(vars[1], '='))
		{
			if (!ft_len_tab(g_var))
			{printf("Esto es len var : %d\n", ft_len_tab(tmp));
				g_bool = 1;
				i = -1;
				j = 0;
				while (vars[++i] && ++j < len)
					g_var[i] = ft_strdup(vars[j]);
				g_var[i] = NULL;
				i = -1;
				while(g_var[++i])
					ft_putstr_fd(g_var[i], 1);
			}
			else if (g_bool)
			{printf("Esto es len var y bool : %d\n", ft_len_tab(tmp));
				i = -1;
				j = 0;
				while (++i < ft_len_tab(tmp))
					g_var[i] = ft_strdup(tmp[i]);
				while (++j < ft_len_tab(vars))
					g_var[i + j] = ft_strdup(vars[j]);
				g_var[i + j] = NULL;
				i = -1;
				while(g_var[++i])
					ft_putstr_fd(g_var[i], 1);
			}
			i = -1;
			j = 0;
			while (vars[++i] && ++j < ft_len_tab(vars))
				g_envp = ft_join_env(g_envp, vars[j]);
			return (1);
		}
		else
			return (1);
		
	}
	return (-1);
}