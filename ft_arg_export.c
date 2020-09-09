/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <fjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 12:33:08 by fernando          #+#    #+#             */
/*   Updated: 2020/09/09 18:10:20 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ft_var_notequal(char *vars)
{
	int		i;
	char	*split;
	char	*copy;
	char 	*aux;
	
	aux = ft_cut_end(vars);
	split = ft_strjoin(aux, "=");
	free(aux);
	i = -1;
	while (g_envp[++i])
	{
		if ((copy = ft_strstr(g_envp[i], split)))
		{
			free(vars);
			vars = ft_strdup("");
		}
	}
	free(split);
}

static void ft_change_var(char *vars)
{
	int		i;
	char	*split;
	char	*copy;
	char 	*aux;
	
	if (ft_strchr(vars, '='))
	{
		aux = ft_cut_end(vars);
		split = ft_strjoin(aux, "=");
		free(aux);
		i = -1;
		while (g_envp[++i])
		{
			if ((copy = ft_strstr(g_envp[i], split)))
				ft_memmove(g_envp[i], "", ft_strlen(g_envp[i]));
			else if ((copy = ft_strstr(g_envp[i], aux)) &&
				!ft_strchr(g_envp[i], '='))
				ft_memmove(g_envp[i], "", ft_strlen(g_envp[i]));
		}
		free(split);
	}
	else
		ft_var_notequal(vars);
}

static char	**ft_join_env(char *vars)
{
	int		i;
	int		len1;
	char	*aux;
	char	**res;
	
	len1 = ft_len_tab(g_envp);
	aux = ft_strdup(ft_realloc_str(vars, -1, 0));
	ft_change_var(aux);
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

static int ft_loop_caracter(char *vars)
{
	int bool;

	bool = 0;
	while (*vars)
	{
		if (*vars == '{' &&  *(vars - 1) == '$')
		{
			bool = 1;
			vars++;
		}
		if (*vars == '}' && bool == 1)
			vars++;
		if (((*vars == '\"'|| *vars == '\'') && *(vars - 1) != '\\') ||
			(*vars == '\\' && *(vars + 1) != '\\'))
			vars++;
		if (*vars == '=')
			break ;
		if (!ft_isalpha(*vars) && !ft_isalnum(*vars) && !ft_isdigit(*vars) &&
			*vars != '_')
			return (0);
		vars++;
	}
	return (1);
}

static int ft_check_var(char *vars)
{
	if ((!ft_isalpha_cm(vars[0]) && vars[0] != '_') ||
		(vars[0] == '\\' && vars[1] == '\\'))
		return (0);
	if (!ft_loop_caracter(vars + 1))
		return (0);
	return (1);
}

void ft_valid_args(char **vars, int *bool)
{
	int j;
	int k;

	j = 0;
	while (vars[++j])
	{
		k = -1;
		while (vars[j][++k])
		{
			if (((!ft_isalpha(vars[j][k]) && k == 0) ||
				(vars[j][k] == '\\' && vars[j][k + 1] == '\\') ||
				vars[j][k] == ' ') && *bool == 0)
			{
				ft_putstr_fd("\033[1;31m", 1);
				ft_putstr_fd("export : not an identifier: ", 1);
				ft_putendl_fd(ft_realloc_str(vars[j], -1, 3), 1);
				*bool = 1;
				break ;
			}
		}
	}	
}

static void ft_check_var_loop(char **vars)
{
	int i;
	int bool;

	i = 0;
	bool = 0;
	while (vars[++i])
	{
		if (!ft_check_var(vars[i]))
		{
			ft_valid_args(vars, &bool);
			ft_memmove(vars[i], "", ft_strlen(vars[i]));
		}
	}
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
		ft_check_var_loop(pcs->cmp);
		i = 0;
		while (pcs->cmp[++i])
		{
			if (!ft_strcmp(pcs->cmp[i], "") && i < ft_len_tab(pcs->cmp) - 1)
				i++;
			g_envp = ft_join_env(pcs->cmp[i]);
		}
	}
	free(aux);
	return (1);
}