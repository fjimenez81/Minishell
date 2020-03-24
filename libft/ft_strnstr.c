/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:44:44 by fjimenez          #+#    #+#             */
/*   Updated: 2019/11/20 11:03:18 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strnstr(const char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*src == '\0')
		return ((char*)dest);
	while (dest[i] != '\0' && i < n)
	{
		if (dest[i] == src[0])
		{
			j = 0;
			while (src[j] != '\0' && dest[i + j] == src[j] && (i + j) < n)
			{
				j++;
				if (src[j] == '\0')
					return ((char*)&dest[i]);
			}
		}
		i++;
	}
	return (0);
}
