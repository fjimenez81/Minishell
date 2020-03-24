/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:42:58 by fjimenez          #+#    #+#             */
/*   Updated: 2019/11/18 12:45:50 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char *ps;

	ps = (char*)s;
	while (*ps != c)
	{
		if (*ps == '\0')
			return (NULL);
		ps++;
	}
	return (ps);
}
