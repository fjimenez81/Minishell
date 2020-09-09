/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <fjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 17:14:03 by fjimenez          #+#    #+#             */
/*   Updated: 2020/09/09 16:08:55 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_join_char(char *s, int c)
{
    int i;
    char *res;

    if (!(res = malloc(sizeof(char) * (ft_strlen(s) + 2))))
        return (NULL);
    i = -1;
    while (s[++i])
        res[i] = s[i];
    res[i] = c;
    i++;
    res[i] = '\0';
    return (res);
}

static void ft_aux_loop(char *str, t_test *tmp)
{
	if (str[tmp->i] == '\"' && str[tmp->i - 1] != '\\' &&
		tmp->d_qu == 0 && tmp->s_qu == 0)
    {
        tmp->i += 1;
		tmp->d_qu = 1;
    }
	else if (str[tmp->i] == '\"' && str[tmp->i - 1] != '\\' && tmp->d_qu == 1)
    {
        tmp->i += 1;
		tmp->d_qu = 0;
    }
	if (str[tmp->i] == '\'' && str[tmp->i - 1] != '\\' &&
		tmp->s_qu == 0 && tmp->d_qu == 0)
    {
        tmp->i += 1;
		tmp->s_qu = 1;
    }
	else if (str[tmp->i] == '\'' && str[tmp->i - 1] != '\\' && tmp->s_qu == 1)
    {
        tmp->i += 1;
		tmp->s_qu = 0;
    }
}

void ft_realloc_aux_two(char *str, t_test *tmp)
{
	ft_aux_loop(str, tmp);
    if (str[tmp->i] == '\\' && (str[tmp->i + 1] == '\'' ||
		str[tmp->i + 1] == '\"'))
            tmp->i += 1;
    else if (str[tmp->i] == '\\' && str[tmp->i + 1] == ' ' &&
		(tmp->d_qu == 1 || tmp->s_qu == 1))
        tmp->i += 1;
	else if (str[tmp->i] == '\\' && (tmp->d_qu == 0 && tmp->s_qu == 0))
		tmp->i += 1;
	else if (str[tmp->i] == '\\' && str[tmp->i + 1] == '\\' &&
		(tmp->d_qu == 0 && tmp->s_qu == 0))
		tmp->i += 1;
    else if (str[tmp->i] == ' ' && str[tmp->i - 1] != '\\' &&
		str[tmp->i + 1] == ' ' && (tmp->d_qu == 0 && tmp->s_qu == 0))
    {  
        while (ft_isspace(str[tmp->i]))
            tmp->i += 1;
        tmp->i -= 1;
    }
}

static void ft_keys_loop(t_test *tmp, int i)
{
	char *aux;

	i = -1;
	while (tmp->dollar[++i] != '}')
	{
		if (tmp->dollar[i] == '{')
			i++;
		aux = ft_join_char(tmp->c_keys, tmp->dollar[i]);
		tmp->c_keys = aux;
		free(aux);
	}
}

char *ft_check_keys(t_test *tmp, int *check)
{
	int i;
	int bool;

	i = -1;
	bool = 0;
	while (tmp->dollar[++i])
	{
		if (tmp->dollar[i] == '{' && bool == 0 && i == 1)
			bool = 1;
		if (tmp->dollar[i] == '}' && bool == 1)
			*check = 1;
		if (*check > 0)
			*check += 1;
	}
	if (*check > 0)
		ft_keys_loop(tmp, i);
	return (tmp->c_keys);
}

char *ft_realloc_var(char *str, char *res, t_test *tmp)
{
	char *var;
	int check;

	check = 0;
	tmp->c_keys = "\0";
    tmp->dollar = ft_cut_end(str + tmp->i);
	tmp->c_keys = ft_check_keys(tmp, &check);
	tmp->c_keys = check > 0 ? ft_strjoin(ft_strrchr(tmp->c_keys, '$') + 1, "=") :
		ft_strjoin(ft_strrchr(tmp->dollar, '$') + 1, "=");
	var = ft_print_var(tmp->c_keys);
	res = ft_strjoin(res, var);
	tmp->i += (!ft_strcmp(var, "") && str[tmp->i + 1] == ' ') ?
		1 : ft_strlen(tmp->dollar) - 1;
	tmp->i -= check > 0 ? check - 2 : 0;
    free(tmp->dollar);
    free(tmp->c_keys);
	return (res);
}

int ft_aux_loop_two(char *str, t_test *tmp)
{
	if ((str[tmp->i] == ' ' && str[tmp->i - 1] != '\\' &&
		(tmp->d_qu == 0 && tmp->s_qu == 0) && tmp->cut == 2) ||
		((str[tmp->i] == '<' || str[tmp->i] == '>' ||
		(str[tmp->i] == ' ' && str[tmp->i + 1] == '>')) &&
		(tmp->d_qu == 0 && tmp->s_qu == 0) && tmp->cut == 1) ||
		(str[tmp->i] == '=' && tmp->cut == 3) || tmp->key == 2)
			return (0);
	return (1);
}

char *ft_only_dollar(char *str, char *aux, char *res, t_test *tmp)
{
	if (str[tmp->i] == '$' && str[tmp->i + 1] == ' ')
		aux = ft_strjoin(res, "$ ");
	else if (str[tmp->i] == '$' && (str[tmp->i + 1] == '\"' ||
		(str[tmp->i + 1] == '\'' && tmp->d_qu == 1) || str[tmp->i + 1] == '\\'))
		aux = ft_join_char(res, str[tmp->i]);
	return (aux);
}

char *ft_realloc_aux_one(char *str, t_test *tmp)
{
	char	*res;
	char	*aux;

	res = "\0";
	while (str[++tmp->i] != '\0')
    {
        ft_realloc_aux_two(str, tmp);
		if (!ft_aux_loop_two(str, tmp))
			break ;
		aux = (str[tmp->i] == '$' && tmp->s_qu == 0) ? ft_strdup(res) :
			ft_join_char(res, str[tmp->i]);
		aux = ft_only_dollar(str, aux, res, tmp);
		res = aux;
		if (str[tmp->i] == '$' && tmp->s_qu == 0)
		{
			res = ft_realloc_var(str, res, tmp);			
			free(aux);
			aux = res;
			res = aux;
		}
		free(aux);	
    }
	return (res);
}

char *ft_realloc_str(char *str, int i, int cut)
{
	char *res;
	t_test tmp;
	int j;
	
	tmp.d_qu = 0;
	tmp.s_qu = 0;
	tmp.cut = cut;
	tmp.i = i;
	tmp.key = 0;
	j = i;
	while (str[++j])
	{
		if (str[j] == '{' && str[j - 1] != '\\')
			tmp.key = 1;
		if (str[j] == '}' && str[j - 1] != '\\'&&
			(str[j + 1] == ' ' || str[j + 1] == '\0') && tmp.key == 0)
		{
			tmp.key = 2;
			ft_putstr_fd("minishell : parse error near \'}\'", 1);
		}
	}
	res = ft_realloc_aux_one(str, &tmp);
	return (res);
}
