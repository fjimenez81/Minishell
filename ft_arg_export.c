/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <fjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 12:33:08 by fernando          #+#    #+#             */
/*   Updated: 2020/07/01 20:10:34 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ft_sort_export(void)
{
	int i;
    int j;
	int len;
	char **export;
    
	export = g_envp;
	len = ft_len_tab(export);
    i = -1;
    while (++i < (len - 1))
	{
        j = i + 1;
        while(++j < len)
            if(ft_strcmp(export[i], export[j]) > 0)
                ft_swap(&export[i], &export[j]);
    }
	i = -1;
	while (export[++i])
	{
		ft_putstr_fd(export[i], 1);
		ft_putchar_fd('\n', 1);
	}
}

static void ft_change_var(char *vars)
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

static char	**ft_join_env(char *vars)
{
	int		i;
	size_t len1;
	char **res;
	
	len1 = ft_len_tab(g_envp);
	if (!(res = (char **)malloc(sizeof(char*) * (len1 + 2))))
		return (NULL);
	ft_change_var(vars);
	i = -1;
	while (g_envp[++i])
		res[i] = ft_strdup(g_envp[i]);
	res[i] = ft_strdup(vars);
	i++;
	res[i] = NULL;
	ft_free_tab(g_envp);
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
		if (!ft_isalnum(*vars) && !ft_isdigit(*vars) && *vars != '_')
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
				if (!ft_strchr(vars[j], '=') || ft_isalnum(*vars[j]))
					break ;
			}
			ft_putstr_fd("\033[1;31m export : no matches found : ", 1);
			ft_putendl_fd(vars[j], 1);
			return (0) ;
		}
	}
	return (1);
}

int		ft_arg_export(t_shell *pcs)
{
	int i;
	int j;

	if (pcs->args == 1)
		ft_sort_export();
	else if (pcs->args > 1)
	{
		if (!ft_check_var_loop(pcs->cmp))
			return (1);
		i = -1;
		j = 0;
		while (pcs->cmp[++i] && ++j < pcs->args)
			g_envp = ft_join_env(pcs->cmp[j]);
	}
	return (1);
}