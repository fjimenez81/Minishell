/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <fjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/23 16:53:06 by fernando          #+#    #+#             */
/*   Updated: 2020/08/02 21:23:01 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2 && *s1 != 0)
	{
		++s1;
		++s2;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

char	*ft_strnew(size_t size)
{
	char	*str;

	if (!(str = (char*)malloc(sizeof(char) * size + 1)))
        return (NULL);
	ft_memset((char*)str, (int)'\0', size + 1);
	return (str);
}

int ft_len_tab(char **args)
{
	int i;

	i = 0;
	while(*args++)
		i++;
	return (i);
}

void	*ft_memalloc(size_t size)
{
	unsigned char *mem;

	if (!(mem = (unsigned char*)malloc(sizeof(size_t) * size)))
        return (NULL);
	ft_bzero(mem, size);
	return (mem);
}

void ft_free_tab(char **str)
{
	int i;

	i = 0;
	while (str[i])
		free(str[i++]);
	(str) ? free(str) : 0;
}

char		*ft_itoa_two(int nbr)
{
	long	n;
	size_t	len;
	char	*str;

	n = nbr;
	len = (n > 0) ? 0 : 1;
	n = (n > 0) ? n : -n;
	while (nbr)
		nbr = len++ ? nbr / 10 : nbr / 10;
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	*(str + len--) = '\0';
	while (n > 0)
	{
		*(str + len--) = n % 10 + '0';
		n /= 10;
	}
	if (len == 0 && str[1] == '\0')
		*(str + len) = '0';
	if (len == 0 && str[1] != '\0')
		*(str + len) = '-';
	return (str);
}