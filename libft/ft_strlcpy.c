/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:43:59 by fjimenez          #+#    #+#             */
/*   Updated: 2019/11/20 10:44:39 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t destsize)
{
	size_t i;

	if (dest == '\0' || src == '\0')
		return (0);
	i = 0;
	while (src[i] != '\0')
		i++;
	if (destsize == 0)
		return (i);
	while (*src && destsize > 1)
	{
		*dest++ = *src++;
		destsize--;
	}
	*dest = '\0';
	return (i);
}
