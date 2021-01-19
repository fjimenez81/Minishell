/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_exe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 17:23:10 by fjimenez          #+#    #+#             */
/*   Updated: 2021/01/13 18:18:13 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_print_error(char *error)
{
	ft_putstr_fd("\033[1;31m[Minishell]: ", 1);
	ft_putstr_fd(error, 1);
	ft_putendl_fd(": command not found", 1);
}

static char	**ft_path_split(void)
{
	int i;

	i = -1;
	while (g_envp[++i])
	{
		if (ft_strstr(g_envp[i], "PATH="))
			return (ft_split(ft_strrchr(g_envp[i], '=') + 1, ':'));
	}
	return (NULL);
}

static void	ft_exe_cmd(t_shell *pcs, t_test *tst, int i, char **aux)
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
		join = ft_strjoin(tmp[j], pcs->cmp[0]);
		free(join);
		exe = execve(join, pcs->cmp, g_envp);
		if (j == ft_len_tab(tmp) - 1 && exe == -1)
		{
			dup2(pcs->std_out, 1);
			ft_err_exit(pcs, tst, i);
		}
	}
	ft_free_tab(tmp);
}

void		ft_not_path(t_shell *pcs, t_test *tst, int i, char **aux)
{
	int exe;

	exe = -1;
	if (aux == NULL)
	{
		exe = execve(pcs->cmp[0], pcs->cmp, g_envp);
		if (exe == -1)
		{
			dup2(pcs->std_out, 1);
			ft_err_exit(pcs, tst, i);
			ft_free_tab(aux);
			ft_free_tab(pcs->cmp);
			exit(127);
		}
	}
}

int			ft_arg_exe(t_shell *pcs, t_test *tst, int i)
{
	char	**aux;
	char	*tmp;

	tmp = ft_realloc_str(tst, pcs->pipesplit[i], -1, 0);
	ft_free_tab(pcs->cmp);
	if ((pcs->pipesplit[i][0] == 34 || pcs->pipesplit[i][0] == 39 ||
		pcs->pipesplit[i][0] == 92) && pcs->args > 1)
		pcs->cmp = ft_split_cmd(pcs->pipesplit[i], ' ');
	else
		pcs->cmp = ft_split_cmd(tmp, ' ');
	aux = ft_path_split();
	ft_not_path(pcs, tst, i, aux);
	ft_exe_cmd(pcs, tst, i, aux);
	free(tmp);
	ft_free_tab(pcs->cmp);
	return (127);
}
