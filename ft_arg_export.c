/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <fjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 12:33:08 by fernando          #+#    #+#             */
/*   Updated: 2020/08/01 19:08:58 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ft_change_var(char *vars)
{
	int		i;
	char	*split;
	char	*copy;
	
	split = ft_cut_end(vars);
	i = -1;
	while (g_envp[++i])
	{
		copy = ft_strstr(g_envp[i], split + 1);
		if (copy != NULL)
			ft_memmove(g_envp[i], "", ft_strlen(g_envp[i]));
	}
	free(split);
}

static char	**ft_join_env(char *vars)
{
	int		i;
	int	len1;
	char	*aux;
	char	**res;
	
	len1 = ft_len_tab(g_envp);
	ft_change_var(vars);
	aux = ft_strdup(ft_realloc_str(vars, -1, 0));
	if (aux[0] == '=')
	{
		ft_putendl_fd("[Minishell] ~> not found", 1);
		free(aux);
		return (g_envp);
	}
	if (!(res = (char **)malloc(sizeof(char*) * (len1 + 2))))
		return (NULL);
	i = -1;
	while (g_envp[++i])
		res[i] = ft_strdup(g_envp[i]);
	res[i] = ft_strdup(aux);
	i++;
	res[i] = NULL;
	ft_free_tab(g_envp);
	free(aux);
	return (res);
}

static int ft_check_var(char *vars)
{
	if (!ft_isalpha(vars[0]) && vars[0] != '_')
		return (0);
	vars++;
	while (*vars)
	{
		if (*vars == '=')
			break ;
		if (!ft_isalpha(*vars) && !ft_isalnum(*vars) && !ft_isdigit(*vars) && *vars != '_')
			return (0);
		vars++;
	}
	return (1);
}

static int ft_check_var_loop(char **vars)
{
	int i;
	int j;

	i = 0;
	while (vars[++i])
	{
		if (!ft_check_var(vars[i]))
		{
			j = 0;
			while (vars[++j])
			{
				if (!ft_isalnum(*vars[j]))
				{
					ft_putstr_fd("\033[1;31m export : no matches found : ", 1);
					ft_putendl_fd(vars[j], 1);
					break ;
				}
			}
			return (0) ;
		}
	}
	return (1);
}

int		ft_arg_export(t_shell *pcs, char *str)
{
	int i;
	char *aux;
	
	aux = ft_pass_space(pcs, str);
	ft_free_tab(pcs->cmp);
	pcs->cmp = ft_split_cmd(aux, ' ');
	if (ft_len_tab(pcs->cmp) == 1)
		ft_sort_export();
	else if (ft_len_tab(pcs->cmp) > 1)
	{
		if (!ft_check_var_loop(pcs->cmp))
		{
			free(aux);
			return (1);
		}
		i = 0;
		while (pcs->cmp[++i])
			g_envp = ft_join_env(pcs->cmp[i]);
		/*if (!(pcs->env = (char**)malloc(sizeof(char*) * (ft_len_tab(g_envp) + 1))))
			return (-1);
		i = -1;
		while (g_envp[++i])
			pcs->env[i] = g_envp[i];
		pcs->env[i] = NULL;*/
	}
	free(aux);
	return (1);
}