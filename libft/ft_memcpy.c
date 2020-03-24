/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:42:19 by fjimenez          #+#    #+#             */
/*   Updated: 2019/11/18 10:42:16 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*pdest;
	char	*psrc;

	pdest = (char*)dest;
	psrc = (char*)src;
	if ((n == 0) || (dest == src))
		return (dest);
	while (n--)
		*pdest++ = *psrc++;
	return (dest);
}
