/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_only_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 07:16:14 by fjimenez          #+#    #+#             */
/*   Updated: 2021/02/08 11:34:06 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_isupper(char *s)
{
	int i;

	i = -1;
	while (s[++i])
	{
		if (s[i] >= 'A' && s[i] <= 'Z')
			return (1);
	}
	return (0);
}

void	ft_change_case(char **s)
{
	int i;

	i = 0;
	while ((*s)[i])
	{
		if ((*s)[i] >= 'A' && (*s)[i] <= 'Z')
			(*s)[i] += 32;
		i++;
	}
}

void	ft_only_path(t_shell *pcs)
{
	char *aux;

	if (!ft_strcmp(pcs->upper[0], "$HOME") ||
		!ft_strcmp(pcs->upper[0], "~") || !ft_strcmp(pcs->upper[0], "~/"))
	{
		aux = ft_get_var("HOME=", 0);
		if (aux || !ft_strcmp(pcs->upper[0], "~"))
			ft_print_error(aux, NULL,
							": is a directory");
		pcs->ret = 126;
		pcs->bool = 1;
		free(aux);
	}
	else if (!ft_strcmp(pcs->upper[0], "$PWD"))
	{
		aux = ft_get_var("PWD=", 0);
		if (aux)
			ft_print_error(aux, NULL,
							": is a directory");
		pcs->ret = 126;
		pcs->bool = 1;
		free(aux);
	}
}
