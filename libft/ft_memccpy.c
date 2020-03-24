/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:40:58 by fjimenez          #+#    #+#             */
/*   Updated: 2019/11/13 13:41:05 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t	i;
	char	*pdest;
	char	*psrc;
	char	*ptr;

	pdest = (char*)dest;
	psrc = (char*)src;
	i = 0;
	ptr = 0;
	while (i < n && ptr == 0)
	{
		pdest[i] = psrc[i];
		if (psrc[i] == ((char)c))
			ptr = pdest + i + 1;
		i++;
	}
	return (ptr);
}
