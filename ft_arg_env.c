/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 13:11:06 by fernando          #+#    #+#             */
/*   Updated: 2020/12/11 13:10:51 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_arg_env(t_shell *pcs)
{
	int i;

	if (pcs->args == 1 || pcs->cmp[0][ft_strlen(pcs->cmp[0]) - 1] == '>')
	{
		i = -1;
		while (g_envp[++i])
			if (ft_strcmp(g_envp[i], "") != 0 && ft_strchr(g_envp[i], '='))
				ft_putendl_fd(g_envp[i], 1);
		return (0);
	}
	ft_putstr_fd("\033[1;31menv: ", 1);
	ft_putstr_fd(pcs->cmp[1], 1);
	ft_putendl_fd(": No such file or directory", 1);
	return (127);
}
