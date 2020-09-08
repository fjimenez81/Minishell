/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <fjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 17:14:03 by fjimenez          #+#    #+#             */
/*   Updated: 2020/09/08 19:43:53 by fjimenez         ###   ########.fr       */
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

char *ft_realloc_var(char *str, char *res, int *i)
{
	char *dollar;
	char *aux;
	char *var;

    dollar = ft_cut_end(str + *i);
	aux = ft_strjoin(ft_strrchr(dollar, '$') + 1, "=");
	var = ft_print_var(aux);
	res = ft_strjoin(res, var);
	*i += (!ft_strcmp(var, "") && str[*i + 1] == ' ') ?
		1 : ft_strlen(dollar) - 1;
    free(dollar);
    free(aux);
	return (res);
}

int ft_aux_loop_two(char *str, t_test *tmp)
{
	if ((str[tmp->i] == ' ' && str[tmp->i - 1] != '\\' &&
		(tmp->d_qu == 0 && tmp->s_qu == 0) && tmp->cut == 2) ||
		((str[tmp->i] == '<' || str[tmp->i] == '>' ||
		(str[tmp->i] == ' ' && str[tmp->i + 1] == '>')) &&
		(tmp->d_qu == 0 && tmp->s_qu == 0) && tmp->cut == 1) ||
		(str[tmp->i] == '=' && tmp->cut == 3))
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
			res = ft_realloc_var(str, res, &tmp->i);			
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
	
	tmp.d_qu = 0;
	tmp.s_qu = 0;
	tmp.cut = cut;
	tmp.i = i;
	res = ft_realloc_aux_one(str, &tmp);
	return (res);
}
