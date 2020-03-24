/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:44:57 by fjimenez          #+#    #+#             */
/*   Updated: 2019/11/19 08:05:39 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char *ulpos;

	ulpos = NULL;
	if (*s == c)
		return (char*)s;
	while (*s++)
	{
		if (*s == c)
			ulpos = (char*)s;
	}
	if (ulpos)
		return (ulpos);
	if (c == '\0')
		return ((char*)s);
	return (0);
}
