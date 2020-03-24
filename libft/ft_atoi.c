/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:36:27 by fjimenez          #+#    #+#             */
/*   Updated: 2019/11/20 10:29:24 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	unsigned long long int	res;
	int						signo;

	res = 0;
	signo = 0;
	while ((*str == 32) || (*str > 8 && *str < 14))
		str++;
	if (*str == '-')
		signo = 1;
	if (*str == '+' || *str == '-')
		str++;
	while ((*str != '\0') && (*str >= '0' && *str <= '9'))
	{
		if (res < 9223372036854775807)
		{
			res = (res * 10) + (*str - '0');
			str++;
		}
		else
			return ((signo - 1) * 1);
	}
	if (signo == 1)
		return (-res);
	return (res);
}
