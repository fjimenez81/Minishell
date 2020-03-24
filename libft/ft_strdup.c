/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:43:10 by fjimenez          #+#    #+#             */
/*   Updated: 2019/11/21 07:37:40 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*ps1;
	char	*res;

	ps1 = (char*)s1;
	i = 0;
	while (ps1[i] != '\0')
		i++;
	if (!(res = (char*)malloc(i + 1)))
		return (NULL);
	i = 0;
	while (ps1[i] != '\0')
	{
		res[i] = ps1[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
