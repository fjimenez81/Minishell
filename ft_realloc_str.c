/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <fjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 17:14:03 by fjimenez          #+#    #+#             */
/*   Updated: 2020/08/03 21:41:17 by fjimenez         ###   ########.fr       */
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

void ft_realloc_aux_two(char *str, int *i, int *quotes)
{
    if ((str[*i] == '\"' || str[*i] == '\'') &&
		str[*i - 1] != '\\' && *quotes == 0)
    {
        *i += 1;
		*quotes = 1;
    }
	else if ((str[*i] == '\"' || str[*i] == '\'') &&
		str[*i - 1] != '\\' && *quotes == 1)
        {
        	*i += 1;
			*quotes = 0;
    }
    else if ((str[*i] == '\\' && (str[*i + 1] == '\'' ||
		str[*i + 1] == '\"')) && *quotes == 1)
            *i += 1;
    else if (str[*i] == '\\' && str[*i + 1] == ' ' && *quotes == 0)
        *i += 1;
    else if (str[*i] == ' ' && str[*i - 1] != '\\' && str[*i + 1] == ' ' &&
        *quotes == 0)
    {  
        while (ft_isspace(str[*i]))
            *i += 1;
        *i -= 1;
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

char *ft_realloc_aux_one(char *str, int i, int cut, int quotes)
{
	char *res;
	char *tmp;

	res = "\0";
	while (str[++i] != '\0')
    {
        ft_realloc_aux_two(str, &i, &quotes);
		if ((str[i] == ' ' && str[i - 1] != '\\' &&
			quotes == 0 && cut == 2) || ((str[i] == '<' || str[i] == '>' ||
			(str[i] == ' ' && str[i + 1] == '>')) && quotes == 0 && cut == 1))
				break ;
		tmp = (str[i] == '$' && quotes == 0) ? ft_strdup(res) :
			ft_join_char(res, str[i]);
		res = tmp;
		if (str[i] == '$' && quotes == 0)
		{	
			res = ft_realloc_var(str, res, &i);			
			free(tmp);
			tmp = res;
			res = tmp;
		}
		free(tmp);	
    }
	return (res);
}

char *ft_realloc_str(char *str, int i, int cut)
{
	char *res;
	int quotes;
	
	quotes = 0;
	res = ft_realloc_aux_one(str, i, cut, quotes);
	return (res);
}

int ft_check_dollar(char *str)
{
	int i;
	int quotes;

	i = -1;
	quotes = 0;
	while (str[++i])
	{
		ft_realloc_aux_two(str, &i, &quotes);
		if (str[i] == '$' && str[i + 1] == '?' && quotes == 0)
			return (1);
	}
	return (0);
}