/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_dollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <fjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 19:40:05 by fjimenez          #+#    #+#             */
/*   Updated: 2020/09/09 16:14:38 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ft_check_aux(char *str, int *i, int *quotes)
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
}

static char *ft_dollar_aux_two(char *str, char *res, t_test *tst)
{
	char  *aux;

	aux = ft_realloc_var(str, res, tst);
	free(aux);
	res = aux;
	return (res);
}

static char *ft_dollar_aux_one(t_test *tst, char *tmp, char *res)
{
	char *aux;

	aux = ft_itoa(WEXITSTATUS(tst->status));
	free(tmp);
	tmp = ft_strjoin(res, aux);
	free(aux);
	tst->i += 1;
	return(tmp);
}

char *ft_check_dollar(t_test *tst, char *str)
{
	int quotes;
	char *tmp;
	char *res;

	res = "\0";
	tst->i = -1;
	quotes = 0;
	while (str[++tst->i])
	{
		ft_check_aux(str, &tst->i, &quotes);
		if ((str[tst->i] == ' ' && str[tst->i - 1] != '\\') && quotes == 0)
			break ;
		tmp = (str[tst->i] == '$' && quotes == 0) ? ft_strdup(res):
		ft_join_char(res, str[tst->i]);
		res = tmp;
		if (str[tst->i] == '$' && str[tst->i + 1] != '?' && quotes == 0)
			res = ft_dollar_aux_two(str, res, tst);
		else if (str[tst->i] == '$' && str[tst->i + 1] == '?' && quotes == 0)
			res = ft_dollar_aux_one(tst, tmp, res);
		free(tmp);
	}
	return (ft_strdup(res));
}
