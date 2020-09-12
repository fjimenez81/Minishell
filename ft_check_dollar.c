/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_dollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <fjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 19:40:05 by fjimenez          #+#    #+#             */
/*   Updated: 2020/09/12 17:28:02 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ft_check_aux(char *str, t_test *tst)
{
    if (str[tst->i] == '\"' && str[tst->i - 1] != '\\' && tst->d_qu == 0)
    {
        tst->i += 1;
		tst->d_qu = 1;
    }
	else if (str[tst->i] == '\"' && str[tst->i - 1] != '\\' && tst->d_qu == 1)
    {
        tst->i += 1;
		tst->d_qu = 0;
    }
	if (str[tst->i] == '\'' && str[tst->i - 1] != '\\' && tst->s_qu == 0)
    {
        tst->i += 1;
		tst->s_qu = 1;
    }
	else if (str[tst->i] == '\'' && str[tst->i - 1] != '\\' && tst->s_qu == 1)
    {
        tst->i += 1;
		tst->s_qu = 0;
    }
    else if ((str[tst->i] == '\\' && (str[tst->i + 1] == '\'' ||
		str[tst->i + 1] == '\"')) && tst->d_qu == 1 && tst->s_qu == 1)
            tst->i += 1;
    else if (str[tst->i] == '\\' && str[tst->i + 1] == ' ' &&
		tst->d_qu == 0 && tst->s_qu == 0)
        tst->i += 1;
}

static char *ft_dollar_aux_two(char *str, char *res, t_test *tst)
{
	char  *aux;

	aux = ft_realloc_var(str, res, tst);
	free(aux);
	res = aux;
	return (res);
}

char *ft_dollar_aux_one(t_test *tst, char *tmp, char *res)
{
	char *aux;

	aux = ft_itoa(WEXITSTATUS(tst->status));
	free(tmp);
	tmp = ft_strjoin(res, aux);
	free(aux);
	tst->i += 1;
	return(tmp);
}

char *ft_check_dollar(t_test *tst, t_shell *pcs, int j, int bool)
{
	int quotes;
	char *tmp;
	char *res;
	char *str;

	res = "\0";
	tst->i = -1;
	tst->d_qu = 0;
	tst->s_qu = 0;
	quotes = 0;
	str = pcs->pipesplit[j];
	/*if (!ft_strcmp(pcs->cmp[0], "echo"))
	{
		tst->i += 5;
		while (ft_isspace(str[tst->i]))
			tst->i += 1;
		tst->i -= 1;
	}*/
	while (str[++tst->i])
	{
		ft_check_aux(str, tst);
		if ((str[tst->i] == ' ' && str[tst->i - 1] != '\\') &&
			tst->d_qu == 0 && tst->s_qu == 0 && bool == 0)
			break ;
		//if (str[tst->i] == '{' || str[tst->i] == '}')
			//tst->i++;
		tmp = (str[tst->i] == '$' && tst->s_qu == 0) ?
			ft_strdup(res) : ft_join_char(res, str[tst->i]);
		res = tmp;
		if (str[tst->i] == '$' && str[tst->i + 1] != '?' && str[tst->i + 1] != '{' && tst->s_qu == 0 &&
			bool == 0)
			res = ft_dollar_aux_two(str, res, tst);
		if (str[tst->i] == '$' && str[tst->i + 1] == '?' && tst->s_qu == 0)
			res = ft_dollar_aux_one(tst, tmp, res);
		free(tmp);
	}
	//ft_putstr_fd("Esto es check dollar : ", 1);
	//ft_putendl_fd(res, 1);
	return (ft_strdup(res));
}
