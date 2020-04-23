/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernando <fernando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 12:33:08 by fernando          #+#    #+#             */
/*   Updated: 2020/04/23 13:54:10 by fernando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ft_change_var(char **g_envp, char *vars)
{
	int		i;
	char	**split;
	char	*copy;
	char	*tmp;

	if (!ft_strchr(vars, '='))
	{
		tmp = vars;
		free(vars);
		vars = ft_strjoin(tmp, "=");
	}
	else
	{
		split = ft_split(vars, '=');
		i = -1;
		while (g_envp[++i])
		{
			copy = ft_strstr(g_envp[i], split[0]);
			if (copy != NULL)
				ft_memmove(g_envp[i], "", ft_strlen(g_envp[i]));
		}
		ft_free_tab(split);
	}
}

static char	**ft_join_env(char **g_envp, char *vars)
{
	int		i;
	size_t len1;
	char **res;
	
	len1 = ft_len_tab(g_envp);
	if (!(res = (char **)malloc(sizeof(char*) * (len1 + 2))))
		return (NULL);
	ft_change_var(g_envp, vars);
	i = -1;
	while (g_envp[++i])
		res[i] = ft_strdup(g_envp[i]);
	res[i] = ft_strdup(vars);
	i++;
	res[i] = NULL;
	ft_free_tab(g_envp);
	return (res);
}

/*static char **ft_var_box(char *vars, int len)
{
	int i;
	int j;
	char **res;

	if (!(res = (char**)malloc(sizeof(char*) * len)))
		return (NULL);
	i = -1;
	j = -1;
	while (++j < len)
		res[j] = ft_strdup(vars);
	res[j] = NULL;
	//ft_strdel(vars);
	return (res);
	
}*/

int		ft_arg_export(char **vars, int args)
{
	int i;
	int j;
	int k;
	//int bool;
	int len;
	
	len = ft_len_tab(vars);
	if (args)
	{
		if (vars[1] == NULL)
		{
			ft_arg_env(vars,args);
            return (1);
		}
		else if (ft_len_tab(vars) > 1)
		{
			/*i = 0;
			bool = 0;
			while (vars[++i])
			{
				if (!ft_strchr(vars[i], '='))
				{
					bool = 1;
					ft_putstr_fd("\033[1;31m[Minishell] : no matches foundd : ", 1);
					ft_putstr_fd(vars[i], 1);
					ft_putstr_fd("\n", 1);
					return (1);
				}
					
			}*/
			i = 0;
			while (vars[++i])
			{
				k = -1;
				j = 0;
				while (vars[++k] && ++j < len)
					g_envp = ft_join_env(g_envp, vars[j]);
			}
			return (1);
			
		}
		else
		{
			ft_putstr_fd("\033[1;31m[Minishell] : ", 1);
			ft_putstr_fd("no matches found : ", 1);
			return (1);
		}
			
	}
	return (-1);
}