/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <fjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:43:22 by fjimenez          #+#    #+#             */
/*   Updated: 2020/07/24 17:15:12 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

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
