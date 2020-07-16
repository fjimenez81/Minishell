/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <fjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 13:11:06 by fernando          #+#    #+#             */
/*   Updated: 2020/07/16 17:40:19 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int             ft_arg_env(t_shell *pcs)
{
	int i;

	if (pcs->args == 1)
	{
		i = -1;
		while (g_envp[++i])
			if (ft_strcmp(g_envp[i], "") != 0)
				ft_putendl_fd(g_envp[i], 1);
		//ft_free_tab(pcs->env);
		return (1);
	}
	return (0);
}