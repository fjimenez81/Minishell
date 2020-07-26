/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <fjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 12:33:08 by fernando          #+#    #+#             */
/*   Updated: 2020/07/26 21:31:10 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **ft_sort_export_aux(int len)
{
	int i;
	int j;

	i = -1;
    while (++i < (len - 1))
	{
        j = i + 1;
        while(j < len - 1)
		{
            if(ft_strcmp(g_export[i], g_export[j]) > 0)
                ft_swap(&g_export[i], &g_export[j]);
			j++;
		}
    }
	return (g_export);
}

static void ft_sort_export(char **str, int bool)
{
	int i;
	int len;
	//char **export;

	len = ft_len_tab(g_envp);
	if(!(g_export = (char**)malloc(sizeof(char*) * len + 1)))
		return ;
	i = -1;
	while (g_envp[++i])
		g_export[i] = ft_strdup(g_envp[i]);
	g_export[i] = NULL;
	g_export = ft_sort_export_aux(len);
	if (bool == 1)
	{
		i = -1;
		while (g_export[++i])
			if (ft_strcmp(g_export[i], "") != 0)
				ft_putendl_fd(g_export[i], 1);
		ft_free_tab(g_export);
	}
	if (bool == 0 && ft_len_tab(str) > 0)
	{
		i = -1;
		while (str[++i])
			if (ft_strcmp(str[i], "") != 0)
				ft_putendl_fd(str[i], 1);
	}
	//ft_free_tab(g_export);
}

static void ft_change_var(char *vars)
{
	int		i;
	char	*split;
	char	*copy;
	char	*tmp;
	char	**exp;
	
	if (!ft_strchr(vars, '='))//Si var no tiene '=' en env no aparece pero si en export var='' 
							//y si haces unset desaparece de las dos listas
	{
		tmp = ft_strjoin(vars, "=''");
		exp = NULL;
		ft_sort_export(exp, 0);
		if (!(exp = (char**)malloc(sizeof(char*) * (ft_len_tab(g_envp) + 2))))
			return ;
		i = -1;
		while (g_export[++i])
			exp[i] = ft_strdup(g_export[i]);
		exp[i] = ft_strdup(tmp);
		i++;
		exp[i] = NULL;
		g_export = exp;
		ft_sort_export(exp, 0);
		//i = -1;
		//while (g_export[++i])
			//ft_putendl_fd(g_export[i], 1);
		free(tmp);
		ft_len_tab(g_export);
		ft_len_tab(exp);
	}
	else
	{
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
}

static char	**ft_join_env(char *vars)
{
	int		i;
	size_t	len1;
	char	*aux;
	char	**res;
	
	len1 = ft_len_tab(g_envp);
	if (!(res = (char **)malloc(sizeof(char*) * (len1 + 2))))
		return (NULL);
	ft_change_var(vars);
	aux = ft_pass_quotes(vars, 0, ft_strlen(vars));
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
	//aux[j] = '\0';
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
	char *tmp;

	tmp = ft_join_char(ft_realloc_str(str, -1, 0), '\0');
	aux = ft_pass_space(pcs, tmp);
	ft_free_tab(pcs->cmp);
	pcs->cmp = ft_split_cmd(aux, ' ');
	if (ft_len_tab(pcs->cmp) == 1)
		ft_sort_export(pcs->cmp, 1);
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
	free(tmp);
	return (1);
}