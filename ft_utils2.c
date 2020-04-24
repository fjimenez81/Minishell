/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernando <fernando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/28 21:33:51 by fernando          #+#    #+#             */
/*   Updated: 2020/04/24 14:24:48 by fernando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int ft_search_c(char *s, int c)
{
	int len;

	len = ft_strlen(s);
	if (s[len] == c)
		return (1);
	else
		return (0);
}*/

int ft_search_c(char *s, int c)
{
    int i;

    i = 0;
    while (s[i])
    {
        if (s[i] == c)
            return (1);
        i++;
    }
    return (0);
}

int 	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f'
			|| c == '\v');
}

void	ignore_space(char **line)
{
	while (ft_isspace(**line))
	*line += 1;
		
}

void ft_swap(char **a, char **b)
{
    char *c;

    c = *a;
    *a = *b;
    *b = c;
}

int		ft_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

