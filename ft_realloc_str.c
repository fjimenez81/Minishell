/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <fjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 17:14:03 by fjimenez          #+#    #+#             */
/*   Updated: 2020/10/05 12:55:22 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int ft_aux_loop_two(char *str, t_test *tmp)
{
	if (((str[tmp->i] == ' ' || str[tmp->i] == '<' || str[tmp->i] == '>') &&
		str[tmp->i - 1] != '\\' && !tmp->d_qu && !tmp->s_qu &&
		tmp->cut == 2) || (str[tmp->i] == '=' && tmp->cut == 3) ||
		tmp->key == 2)
		return (0);
	if ((str[tmp->i] == '<' || str[tmp->i] == '>' ||
		(str[tmp->i] == ' ' && str[tmp->i + 1] == '>')) &&
		str[tmp->i - 1] != '\\' && !tmp->d_qu && !tmp->s_qu &&
		tmp->cut == 1)
			return (0);
	return (1);
}

static char *ft_only_dollar(char *str, char *aux, char *res, t_test *tmp)
{
	if (str[tmp->i] == '$' && str[tmp->i + 1] == ' ')
		aux = ft_strjoin(res, "$ ");
	else if (str[tmp->i] == '$' && (str[tmp->i + 1] == '\"' ||
		(str[tmp->i + 1] == '\'' && tmp->d_qu == 1) || str[tmp->i + 1] == '\\'))
		aux = ft_join_char(res, str[tmp->i]);
	return (aux);
}

static char *ft_realloc_aux_one(char *str, t_test *tmp)
{
	char	*res;
	char	*aux;

	res = "\0";
	while (str[++tmp->i] != '\0')
    {
        ft_realloc_aux_two(str, tmp);
		if (!ft_aux_loop_two(str, tmp))
			break ;
		aux = (str[tmp->i] == '$' && str[tmp->i - 1] != '\\' &&
			tmp->s_qu == 0) ? ft_strdup(res) :
			ft_join_char(res, str[tmp->i]);
		aux = ft_only_dollar(str, aux, res, tmp);
		res = aux;
		if (str[tmp->i] == '$' && str[tmp->i - 1] != '\\' && tmp->s_qu == 0)
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

char *ft_realloc_str(t_test *tmp, char *str, int i, int cut)
{
	char *res;
	int j;
	
	tmp->d_qu = 0;
	tmp->s_qu = 0;
	tmp->cut = cut;
	tmp->i = i;
	tmp->key = 0;
	j = i;
	while (str[++j])
	{
		if (str[j] == '{' && str[j - 1] != '\\')
			tmp->key = 1;
		if (str[j] == '}' && str[j - 1] != '\\'&&
			(str[j + 1] == ' ' || str[j + 1] == '\0') && tmp->key == 0)
		{
			tmp->key = 2;
			ft_putstr_fd("minishell : parse error near \'}\'", 1);
		}
	}
	res = ft_realloc_aux_one(str, tmp);
	return (res);
}
