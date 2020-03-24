/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:41:17 by fjimenez          #+#    #+#             */
/*   Updated: 2019/11/15 12:59:49 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*ps;

	i = 0;
	ps = (char*)s;
	while (i < n)
	{
		if (ps[i] == (char)c)
			return ((void*)ps + i);
		i++;
	}
	return (NULL);
}
