/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <fjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/28 21:33:51 by fernando          #+#    #+#             */
/*   Updated: 2020/07/25 17:14:39 by fjimenez         ###   ########.fr       */
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

char *ft_realloc_str(char *str, int i, int cut)
{
    int quotes;
    int bool;
	char *tmp;
	char *res;
    char *dollar;
    char *aux;
    char *var;
	
	res = "\0";
    bool = 0;
    quotes = 0;
	while (str[++i] != '\0')
    {
        if ((str[i] == '\"' || str[i] == '\'') &&
				str[i - 1] != '\\' && quotes == 0)
                {
                    i++;
				    quotes = 1;
                }
		else if ((str[i] == '\"' || str[i] == '\'') &&
				str[i - 1] != '\\' && quotes == 1)
                {
                    i++;
				    quotes = 0;
                }
        else if ((str[i] == '\\' && (str[i + 1] == '\'' ||
				str[i + 1] == '\"')) && quotes == 1)
                    i++;
        else if (str[i] == '\\' && str[i + 1] == ' ' && quotes == 0)
            i++;
        else if (str[i] == ' ' && str[i - 1] != '\\' && str[i + 1] == ' ' &&
             quotes == 0)
        {  
            while (ft_isspace(str[i]))
                i += 1;
            i--;
        }
		else if (str[i] == '-' && str[i + 1] == 'n' && str[i + 2] == ' ' &&
			quotes == 0 && cut == 0)
			i += 3;
        else if ((str[i] == '<' || str[i] == '>' || (str[i] == ' ' &&
             str[i + 1] == '>')) && quotes == 0 && cut == 1)
            {
                break ;
            }
        if (str[i] == '$' && bool == 0 && quotes == 0)
        {  
            bool = 1;
            tmp = ft_join_char(res, '\0');
        }
        else
            tmp = ft_join_char(res, str[i]);
		res = tmp;
		if (str[i] == '$' && bool == 1 && quotes == 0)
		{
            bool = 0;
            dollar = ft_cut_end(str + i);
			aux = ft_strjoin(ft_strrchr(dollar, '$') + 1, "=");
			var = ft_print_var(aux);
			free(tmp);
			tmp = ft_strjoin(res, var);
			res = tmp;
			i += ft_strlen(dollar) - 1;
            if (!ft_strcmp(var, "") && str[i + 1] == ' ')
                i++;
            free(dollar);
            free(aux);
		}
		free(tmp);
    }
	if (cut == 1)
	{
    	tmp = ft_join_char(res, '\0');
		free(res);
		res = tmp;
	}
	return (res);
}
