/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:02:17 by fjimenez          #+#    #+#             */
/*   Updated: 2021/01/23 16:09:00 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_check_n(char *s)
{
	int i;

	i = -1;
	if (!ft_strcmp(s, ""))
		return (0);
	while (s[++i])
	{
		if (i == 0 && s[i] == '-' && s[i + 1] == '-')
			return (0);
		if (i == 0 && s[i] == 'n')
			return (0);
		if (s[i] == '-' && s[i + 1] == 'n')
			i++;
		if (s[i] == 'n' && s[i + 1] == '-')
			i++;
		if (s[i] != 'n')
			return (0);
	}
	return (1);
}

char	*ft_quit_n(char *s)
{
	int i;
	int j;

	i = -1;
	while (s[++i])
	{
		if (s[i] == 92)
			i++;
		if (s[i] == '-' && s[i + 1] == 'n')
		{
			i++;
			j = 0;
			while (s[i] == 'n')
			{
				j++;
				i++;
			}
			if (s[i] != 'n' && s[i] != 34 && s[i] != 39 && s[i] != ' ')
				return (s + i - j - 1);
		}
		if (s[i] != 'n' && s[i] != 34 && s[i] != 39 && s[i] != ' ')
			break ;
	}
	return (s + i);
}
