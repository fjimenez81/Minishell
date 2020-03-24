/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:43:22 by fjimenez          #+#    #+#             */
/*   Updated: 2019/11/27 08:55:01 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	size_t	lens1;
	size_t	lens2;
	size_t	i;
	size_t	j;

	if (s1 == '\0' || s2 == '\0')
		return (NULL);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	if (!(dest = ft_calloc((lens1 + lens2) + 1, 1)))
		return (NULL);
	i = -1;
	j = -1;
	while (++i < lens1)
		*(dest + i) = *(s1 + i);
	while (++j < lens2)
		*(dest + i++) = *(s2 + j);
	return (dest);
}
