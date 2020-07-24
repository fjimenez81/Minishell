/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pass_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <fjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 19:00:50 by fjimenez          #+#    #+#             */
/*   Updated: 2020/07/23 18:45:13 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_pass_quotes2(char *res, char *s, int k, int size)
{
	int j;
    int quotes;

	j = 0;
    quotes = 0;
    while (s[k] && size > 0)
    {
        if (((s[k] == '\"' && s[k - 1] != '\\') ||
            (s[k] == '\'' && s[k - 1] != '\\')) && quotes == 0)
            quotes = 1;
        else if (((s[k] == '\"' && s[k - 1] != '\\') ||
            (s[k] == '\'' && s[k - 1] != '\\')) && quotes == 1)
            quotes = 0;
        if ((s[k] == '\\' && s[k + 1] == '\"') ||
            (s[k] == '\\' && s[k + 1] == '\'') ||
            (s[k] == '\\' && s[k + 1] == ' ') ||
            (s[k] != '\"' && s[k] != '\''))
        {
            if (((s[k] == '\\' && s[k + 1] == '\"') ||
                (s[k] == '\\' && s[k + 1] == '\'') ||
                (s[k] == '\\' && s[k + 1] == ' ')) && quotes == 0)
                    k++;
            res[j] = s[k];
            j++;
            size--;
        }
        k++;
    }
    res[j] = '\0';
	return (res);
}

char *ft_pass_quotes(char *s, int n, int size)
{
    int i;
	int k;
    int len;
    char *res;

    i = 0;
	k = n;
    len = size;
    while (s[n] && len > 0)
    {
        if ((s[n] == '\\' && s[n + 1] == '\"') ||
            (s[n] == '\\' && s[n + 1] == '\'') ||
            (s[n] == '\\' && s[n + 1] == ' ') ||
            (s[n] != '\"' && s[n] != '\''))
            {
                i++;
                len--;
            }
        n++;
    }
    if (!(res = malloc(sizeof(char) * i + 1)))
        return (NULL);
    return (ft_pass_quotes2(res, s, k, size));
}

/*char *ft_special_dollar(char *s)
{
    int i;
    int j;
    int quotes;
    char *dollar;
    char *aux;
    char *tmp;
    //char *var;

    i = -1;
    quotes = 0;
    while (s[++i])
    {
        if (((s[i] == '\"' && s[i - 1] != '\\') ||
            (s[i] == '\'' && s[i - 1] != '\\')) && quotes == 0)
            quotes = 1;
        else if (((s[i] == '\"' && s[i - 1] != '\\') ||
            (s[i] == '\'' && s[i - 1] != '\\')) && quotes == 1)
            quotes = 0;
        else if ((s[i] == '$' && s[i + 1] != ' ' &&
			s[i + 1] != '\0') && quotes == 0)
            {
                dollar = ft_cut_end(s + i);
				aux = ft_strjoin(ft_strrchr(dollar, '$') + 1, "=");
                //var = ft_print_var(aux);
				j += ft_strlen(ft_print_var(aux)) - ft_strlen(dollar);
				i += ft_strlen(dollar);
				free(aux);
				free(dollar);
            }
    }
    if (!(dollar = malloc(sizeof(char) * (i + j))))
        return (NULL);
    i = -1;
    quotes = 0;
    while (s[++i])
    {
        if (((s[i] == '\"' && s[i - 1] != '\\') ||
            (s[i] == '\'' && s[i - 1] != '\\')) && quotes == 0)
            quotes = 1;
        else if (((s[i] == '\"' && s[i - 1] != '\\') ||
            (s[i] == '\'' && s[i - 1] != '\\')) && quotes == 1)
            quotes = 0;
        else if ((s[i] == '$' && s[i + 1] != ' ' &&
			s[i + 1] != '\0') && quotes == 0)
            {
                tmp = ft_cut_end(s + i);
				aux = ft_strjoin(ft_strrchr(tmp, '$') + 1, "=");
                //var = ft_print_var(aux);
				j += ft_strlen(ft_print_var(aux)) - ft_strlen(dollar);
				i += ft_strlen(dollar);
				free(aux);
				free(dollar);
            }
        
    }

}*/