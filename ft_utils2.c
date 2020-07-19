/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <fjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/28 21:33:51 by fernando          #+#    #+#             */
/*   Updated: 2020/07/19 21:24:06 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	c = (unsigned char)c;
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' \
		|| c == ' ')
		return (1);
	return (0);
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

char *ft_cut_end(char *s)
{
    int i;
    int j;
    char *dest;
    
    i = -1;
    while (s[++i])
    {
        if (s[i] == '\"' || s[i] == '\'' || s[i] == ' '||
            s[i] == '\\' || s[i] == '\0' || s[i] == '=')
            break ;
        else if (ft_isdigit(s[i]) == 1)
            return (NULL);    
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
