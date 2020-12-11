/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_exe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 17:23:10 by fjimenez          #+#    #+#             */
/*   Updated: 2020/12/11 16:16:13 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_check_path(int *check, int i)
{
	int		k;
	char	**tmp;
	char	*aux;

	aux = ft_substr(g_envp[i], 5, ft_strlen(g_envp[i]));
	tmp = ft_split(aux, ':');
	k = -1;
	*check = 0;
	while (tmp[++k])
	{
		if (ft_strstr(tmp[k], "/usr/bin") ||
			ft_strstr(tmp[k], "/bin"))
			*check = 1;
	}
	free(aux);
	ft_free_tab(tmp);
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
			if (ft_strrchr(g_envp[i], '=') + 1 != '\0')
				ft_check_path(&check, i);
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

int			ft_arg_exe_aux(t_shell *pcs, t_test *tst, int i)
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
		//free(join);
		if (ft_path(j))
			exe = execve(join, pcs->cmp, g_envp);
		free(join);
		if (j == 3 && exe == -1 && ft_strlen(pcs->cmp[0]) != 0)
		{
			dup2(pcs->std_out, 1);
			ft_err_exit(pcs, tst, i);
			return (0);
		}
	}
	return (1);
}

int			ft_arg_exe(t_shell *pcs, t_test *tst, int i)
{
	char *aux;

	aux = ft_realloc_str(tst, pcs->pipesplit[i], -1, 1);
	ft_free_tab(pcs->cmp);
	if (pcs->pipesplit[i][0] == '\"' || pcs->pipesplit[i][0] == '\'')
		pcs->cmp = ft_split(pcs->pipesplit[i], '\"' | '\'');
	else
		pcs->cmp = ft_split_cmd(aux, ' ');
	if (!ft_arg_exe_aux(pcs, tst, i))
		return (127);
	return (0);
}
