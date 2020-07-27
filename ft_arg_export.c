/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <fjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 12:33:08 by fernando          #+#    #+#             */
/*   Updated: 2020/07/27 17:12:04 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **ft_sort_export_aux(char **export, int len)
{
	int i;
	int j;

	i = -1;
    while (++i < (len - 1))
	{
        j = i + 1;
        while(j < len - 1)
		{
            if(ft_strcmp(export[i], export[j]) > 0)
                ft_swap(&export[i], &export[j]);
			j++;
		}
    }
	return (export);
}

void ft_print_export(char **export, int i)
{
	char *tmp;

	if (ft_strcmp(export[i], "") != 0 && ft_strchr(export[i], '='))
		ft_putendl_fd(export[i], 1);
	else if (!ft_strchr(export[i], '=') && ft_strcmp(export[i], "") != 0)
	{
		tmp = export[i];
		free(export[i]);
		export[i] = ft_strjoin(tmp, "=''");
		ft_putendl_fd(export[i], 1);
	}
}

static void ft_sort_export()
{
	int i;
	int len;
	char **export;

	len = ft_len_tab(g_envp);
	if(!(export = (char**)malloc(sizeof(char*) * len + 1)))
		return ;
	i = -1;
	while (g_envp[++i])
		export[i] = ft_strdup(g_envp[i]);
	export[i] = NULL;
	export = ft_sort_export_aux(export, len);
	i = -1;
	while (export[++i])
		ft_print_export(export, i);
	ft_free_tab(export);
}

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
	size_t	len1;
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

void ft_pass_space_two(char *str, int *i, int *size)
{
	int equal;
	int quotes;

	equal = 0;
	quotes = 0;
	while (str[++*i])
	{
		if (str[*i] == '=' && equal == 0)
			equal = 1;
		if ((str[*i] == '\"' || str[*i] == '\'') && str[*i - 1] != '\\' && equal == 1 && quotes == 0)
			quotes = 1;
		else if ((str[*i] == '\"' || str[*i] == '\'') && str[*i - 1] != '\\' && equal == 1 && quotes == 1)
			quotes = 0;
		if (str[*i] != ' ' && str[*i + 1] == ' ' && str[*i] != '\\' && equal == 1 && quotes == 0)
			equal = 0;
		else if (str[*i] == '\\' && str[*i + 1] == ' ' && quotes == 0 && equal == 1)
		{
			*i += 1;
			*size += 1;
		}
	}
}

void ft_pass_space_four(t_shell *pcs, char *str, int i)
{
	if (str[i] == '=' && pcs->equal == 0)
		pcs->equal = 1;
	if ((str[i] == '\"' || str[i] == '\'') && str[i - 1] != '\\' &&
		pcs->equal == 1 && pcs->quotes == 0)
		pcs->quotes = 1;
	else if ((str[i] == '\"' || str[i] == '\'') && str[i - 1] != '\\' &&
		pcs->equal == 1 && pcs->quotes == 1)
		pcs->quotes = 0;
	if (str[i] != ' ' && str[i + 1] == ' ' && str[i] != '\\' &&
		pcs->equal == 1 && pcs->quotes == 0)
		pcs->equal = 0;
}

char *ft_pass_space_three(t_shell *pcs, char *str, char *aux)
{
	int i;
	int j;

	i = -1;
	j = 0;
	pcs->equal = 0;
	pcs->quotes = 0;
	while (str[++i])
	{
		ft_pass_space_four(pcs, str, i);
		if (str[i] == '\\' && str[i + 1] == ' ' &&
			pcs->quotes == 0 && pcs->equal == 1)
		{
			aux[j] = '\"';
			j++;
			aux[j] = ' ';
			j++;
			aux[j] = '\"';
			i += 2;
			j++;
		}
		aux[j] = str[i];
		j++;	
	}
	return (aux);
}

char *ft_pass_space(t_shell *pcs, char *str)
{
	int i;
	int size;
	char *pass;

	i = -1;
	ft_pass_space_two(str, &i, &size);
	pass = ft_strnew(size + i);
	return (ft_pass_space_three(pcs, str, pass));
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
	}
	free(aux);
	return (1);
}