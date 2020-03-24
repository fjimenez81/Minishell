/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:42:31 by fjimenez          #+#    #+#             */
/*   Updated: 2019/11/18 12:07:33 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*pdest;
	char	*psrc;
	char	*pdfinal;
	char	*psfinal;

	pdest = (char*)dest;
	psrc = (char*)src;
	if ((n == 0) || (dest == src))
		return (dest);
	if (pdest < psrc)
	{
		while (n--)
			*pdest++ = *psrc++;
		return (dest);
	}
	pdfinal = pdest + n - 1;
	psfinal = psrc + n - 1;
	while (n--)
		*pdfinal-- = *psfinal--;
	return (dest);
}
