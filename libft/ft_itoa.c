/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <fjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 19:49:48 by fjimenez          #+#    #+#             */
/*   Updated: 2020/01/22 13:21:56 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

static void	ft_putnbr(char *str, int nbr)
{
	int		nb_digits;
	int		digits;
	long	long_nb;

	nb_digits = 1;
	long_nb = nbr;
	digits = 1;
	while (nbr > 9 || nbr < -9)
	{
		nb_digits++;
		digits *= 10;
		nbr /= 10;
	}
	if (long_nb < 0)
	{
		*str++ = '-';
		long_nb = -long_nb;
	}
	while (nb_digits--)
	{
		*str++ = long_nb / digits + '0';
		long_nb %= digits;
		digits /= 10;
	}
	*str = '\0';
}

char		*ft_itoa(int nb)
{
	char	*str;
	size_t	size;
	int		nbr;

	size = 1;
	nbr = nb;
	while (nb > 9 || nb < -9)
	{
		++size;
		nb /= 10;
	}
	if (nb < 0)
		++size;
	if (!(str = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	ft_putnbr(str, nbr);
	return (str);
}
