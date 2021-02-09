/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 13:11:06 by fernando          #+#    #+#             */
/*   Updated: 2021/02/05 10:59:03 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_env_aux(t_shell *p, int bool, int i)
{
	char	*aux;
	char	*tmp;
	int		check;

	if (bool && p->args == 1)
	{
		tmp = ft_realloc_str(p->upper[0], -1, 0);
		aux = ft_strjoin("_=/usr/bin/", tmp);
		while (g_envp[++i])
		{
			check = 0;
			if (g_envp[i][0] == '_' && g_envp[i][1] == '=')
				check = 1;
			if (ft_strcmp(g_envp[i], "") != 0 && ft_strchr(g_envp[i], '=') &&
				!check)
				ft_putendl_fd(g_envp[i], p->fd);
		}
		ft_putendl_fd(aux, p->fd);
		free(aux);
		free(tmp);
		return (0);
	}
	return (1);
}

static int	ft_check_env(int i)
{
	int		j;
	char	**tmp;

	while (g_envp[++i])
	{
		if (!ft_strncmp(g_envp[i], "PATH=", 5))
		{
			tmp = ft_split(ft_first_ap(g_envp[i], '=') + 1, ':');
			j = -1;
			while (tmp[++j])
			{
				if (!ft_strncmp(tmp[j], "/usr/bin", 8))
				{
					ft_free_tab(tmp);
					return (1);
				}
			}
			ft_free_tab(tmp);
		}
	}
	return (0);
}

int			ft_arg_env(t_shell *p)
{
	int bool;

	bool = ft_check_env(-1);
	if (!ft_env_aux(p, bool, -1))
		return (0);
	if (!bool)
		ft_print_error(p->upper[0], NULL, ": No such file or directory");
	else
	{
		ft_putstr_fd("\033[1;31menv: ", 1);
		ft_putstr_fd(p->cmp[1], 1);
		ft_putendl_fd(": No such file or directory", 1);
	}
	return (127);
}
