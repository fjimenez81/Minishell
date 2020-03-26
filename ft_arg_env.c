/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernando <fernando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 13:11:06 by fernando          #+#    #+#             */
/*   Updated: 2020/03/26 12:29:53 by fernando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		print_env(char **env)
{
	int i;

	i = -1;
	while (env[++i])
		if (ft_strcmp(env[i], "") != 0)
			ft_putendl_fd(env[i], 1);
	return (1);
}

int             ft_arg_env(char **vars, int args)
{
    //char	**tmpenv;

    (void)vars;
	if (args == 1)
		return (print_env(g_envp));
	/*else
	{
		tmpenv = ft_tabcpy(g_envp);
		//env_help(args, tmpenv);
		//free_command(tmpenv);
	}*/
	return (1);
}