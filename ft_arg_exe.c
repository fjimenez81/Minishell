/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_exe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 17:23:10 by fjimenez          #+#    #+#             */
/*   Updated: 2021/02/08 21:08:00 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_print_error(char *error, char *path, char *s)
{
	ft_putstr_fd("\033[1;31m[Minishell]: ", 2);
	if (path)
		ft_putstr_fd(path, 2);
	ft_putstr_fd(error, 2);
	ft_putendl_fd(s, 2);
}

static char	**ft_path_split(void)
{
	int i;

	i = -1;
	while (g_envp[++i])
	{
		if (!ft_strncmp(g_envp[i], "PATH=", 5))
			return (ft_split(ft_first_ap(g_envp[i], '=') + 1, ':'));
	}
	return (NULL);
}

static void	ft_exe_cmd(t_shell *p, char **aux)
{
	char	*join;
	char	**tmp;
	int		exe;
	int		j;

	exe = -1;
	j = -1;
	tmp = ft_add_str(aux);
	while (exe == -1 && ++j < ft_len_tab(tmp))
	{
		join = ft_strjoin(tmp[j], p->cmp[0]);
		exe = execve(join, p->cmp, g_envp);
		free(join);
		if (j == ft_len_tab(tmp) - 1 && exe == -1)
		{
			ft_err_exit(p);
			ft_free_tab(p->cmp);
		}
	}
	ft_free_tab(tmp);
}

static void	ft_point_exe(t_shell *p)
{
	if (!ft_strcmp(p->cmp[0], ".") && !p->cmp[1])
	{
		ft_print_error(".", NULL, " filename argument required");
		ft_putendl_fd(".: usage: . filename [arguments]", 2);
		exit (2);
	}
	else if (!ft_strcmp(p->cmp[0], ".") && p->cmp[1])
	{
		ft_print_error(p->cmp[1], NULL, ": No such file or directory");
		exit (1);
	}
}

void		ft_arg_exe(t_shell *p)
{
	char	**aux;
	int		exe;

	ft_point_exe(p);
	aux = ft_path_split();
	exe = -1;
	if (aux == NULL)
	{
		exe = execve(p->cmp[0], p->cmp, g_envp);
		if (exe == -1)
		{
			ft_err_exit(p);
			ft_free_tab(p->cmp);
			exit(127);
		}
	}
	ft_exe_cmd(p, aux);
}
