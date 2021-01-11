/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_exe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 17:23:10 by fjimenez          #+#    #+#             */
/*   Updated: 2021/01/11 16:46:59 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_check_path(int *check)
{
	int		k;

	k = -1;
	*check = 0;
	while (g_envp[++k])
	{
		if (ft_strstr(g_envp[k], "/usr/bin:") ||
			ft_strstr(g_envp[k], "/bin:"))
			*check = 1;
	}
}

static	int	ft_path(int j)
{
	int i;
	int check;

	i = -1;
	if (j == 3)
		return (1);
	while (g_envp[++i])
	{
		if (ft_strstr(g_envp[i], "PATH="))
		{
			check = 1;
			if (ft_strrchr(g_envp[i], '=') + 1)
				ft_check_path(&check);
			return (check);
		}
	}
	return (0);
}

void		ft_print_error(char *error)
{
	ft_putstr_fd("\033[1;31m[Minishell]: ", 1);
	ft_putstr_fd(error, 1);
	ft_putendl_fd(": command not found", 1);
}

static void	ft_arg_exe_aux(t_shell *pcs, t_test *tst, int i)
{
	char	*join;
	int		exe;
	int		j;

	exe = -1;
	j = 0;
	while (exe == -1 && j < 3)
	{
		join = ft_strjoin(tst->paths[j], pcs->cmp[0]);
		j++;
		if (ft_path(j))
			exe = execve(join, pcs->cmp, g_envp);
		free(join);
		if (j == 3 && exe == -1)
		{
			dup2(pcs->std_out, 1);
			ft_err_exit(pcs, tst, i);
		}
	}
}

int			ft_arg_exe(t_shell *pcs, t_test *tst, int i)
{
	char *aux;

	aux = ft_realloc_str(tst, pcs->pipesplit[i], -1, 1);
	ft_free_tab(pcs->cmp);
	if (pcs->pipesplit[i][0] == '\"' || pcs->pipesplit[i][0] == '\'')
		pcs->cmp = ft_split(aux, '\"' | '\'');
	else
		pcs->cmp = ft_split_cmd(aux, ' ');
	ft_arg_exe_aux(pcs, tst, i);
	free(aux);
	ft_free_tab(pcs->cmp);
	return (127);
}
