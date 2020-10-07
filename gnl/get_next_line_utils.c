/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 07:36:50 by fjimenez          #+#    #+#             */
/*   Updated: 2020/10/07 19:08:59 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "../minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (*s)
	{
		i++;
		s++;
	}
	return (i);
}

char	*ft_strchr(const char *s1, int c)
{
	while (*s1)
	{
		if (*s1 == (char)c)
			return ((char*)s1);
		s1++;
	}
	if ((char)c == '\0')
		return ((char*)s1);
	return (NULL);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*dest;
	size_t	lens1;
	size_t	lens2;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	if (!(dest = (char*)malloc(sizeof(char) * (lens1 + lens2) + 1)))
		return (NULL);
	i = -1;
	j = -1;
	while (++i < lens1)
		*(dest + i) = *(s1 + i);
	while (++j < lens2)
		*(dest + i++) = *(s2 + j);
	dest[i++] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s)
{
	char		*ps;
	char		*res;
	size_t		len;
	size_t		i;

	ps = (char*)s;
	len = ft_strlen(s);
	if (!(res = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	i = 0;
	while (ps[i] != '\0')
	{
		res[i] = ps[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	i;
	size_t	size;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	size = ft_strlen(s + start);
	if (size < len)
		len = size;
	if (!(dest = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	while (i < len)
	{
		dest[i] = s[start + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
