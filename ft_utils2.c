/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <fjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/28 21:33:51 by fernando          #+#    #+#             */
/*   Updated: 2020/08/04 15:55:42 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int 	ft_isspace(int c)
{
	c = (unsigned char)c;
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' \
		|| c == ' ')
		return (1);
	return (0);
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
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '$');
}

char *ft_cutstr(char *src, char *cut)
{
    size_t i;
    size_t j;

	if (!ft_strcmp(cut, ""))
        return (src);
    i = -1;
    j = 0;
    while (src[++i])
    {
        if (src[i] == cut[j])
            j++;
        else
            j = 0;
        if (cut[j] == '\0')
        {
            i++;
            while(ft_isspace(src[i]))
            {
                i += 1;
                j += 1;
            }
            return (src + j);   
        }    
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
            s[i] == '\\' || s[i] == '\0' || s[i] == '=' ||
            (s[i] == '$' && (s[i + 1] == '\0' || s[i + 1] != ' ') && i != 0))
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
