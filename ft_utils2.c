/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernando <fernando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/28 21:33:51 by fernando          #+#    #+#             */
/*   Updated: 2020/05/07 20:34:40 by fernando         ###   ########.fr       */
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

void	ignore_space(char **command)
{
	while (ft_isspace(**command))
        **command += 1;
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

int ft_first_chr(char **s, char c)
{
    if (*s[0] == c)
        return (1);
    return (0);
}

char *ft_cutstr(char *src, char *cut, size_t len)
{
    size_t i;
    size_t j;

	if (!ft_strcmp(cut, ""))
        return (src);
    i = -1;
    j = 0;
    while (src[++i] && i < len)
    {
        if (src[i] == cut[j])
            j++;
        else
            j = 0;
        if (cut[j] == '\0')
            return (src + j);
    }
    return (NULL);
}

char *ft_cut_end(char *s, int a, int b, int c)
{
    int i;
    int j;
    char *dest;
    
    i = -1;
    while (s[++i])
    {
        if (s[i] == a || s[i] == b || s[i] == c)
            break ;
    }
    if (!(dest = (char*)malloc(sizeof(char) * i + 1)))
        return (NULL);
    j = -1;
    while (s[++j] && i > 0)
    {
        dest[j] = s[j];
        i--;
    }
    dest[j] = '\0';
    return (dest);
}