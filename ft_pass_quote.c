/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pass_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <fjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 19:00:50 by fjimenez          #+#    #+#             */
/*   Updated: 2020/07/09 20:04:31 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_pass_quotes2(char *res, char *s, int k, int size)
{
	int j;

	j = 0;
    while (s[k] && size > 0)
    {
        if ((s[k] == '\\' && s[k + 1] == '\"') ||
            (s[k] == '\\' && s[k + 1] == '\'') ||
            (s[k] == '\\' && s[k + 1] == ' ') ||
            (s[k] != '\"' && s[k] != '\''))
        {
            if ((s[k] == '\\' && s[k + 1] == '\"') ||
                (s[k] == '\\' && s[k + 1] == '\'') ||
                (s[k] == '\\' && s[k + 1] == ' '))
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
