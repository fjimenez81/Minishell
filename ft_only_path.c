/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_only_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 07:16:14 by fjimenez          #+#    #+#             */
/*   Updated: 2021/01/21 08:19:23 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_only_path_aux(t_shell *pcs, t_test *t)
{
	if (!ft_strcmp(pcs->cmp[0], "$PATH"))
	{
		if (ft_get_var(t, "PATH", 0))
		{
			ft_putstr_fd("\033[1;31m[Minishell]: ", 1);
			ft_putstr_fd(ft_get_var(t, "PATH", 0), 1);
			ft_putendl_fd(": No such file or directory", 1);
		}
		return (0);
	}
	return (1);
}

int			ft_only_path(t_shell *pcs, t_test *t)
{
	if (!ft_strcmp(pcs->cmp[0], "$HOME"))
	{
		if (ft_get_var(t, "HOME", 0))
		{
			ft_putstr_fd("\033[1;31m[Minishell]: ", 1);
			ft_putstr_fd(ft_get_var(t, "HOME", 0), 1);
			ft_putendl_fd(": is a directory", 1);
			t->status = 126;
		}
		return (0);
	}
	else if (!ft_strcmp(pcs->cmp[0], "$PWD"))
	{
		if (ft_get_var(t, "PWD", 0))
		{
			ft_putstr_fd("\033[1;31m[Minishell]: ", 1);
			ft_putstr_fd(ft_get_var(t, "PWD", 0), 1);
			ft_putendl_fd(": is a directory", 1);
			t->status = 126;
		}
		return (0);
	}
	else if (!ft_only_path_aux(pcs, t))
		return (0);
	return (1);
}
