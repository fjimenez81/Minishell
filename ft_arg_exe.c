/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_exe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 17:23:10 by fjimenez          #+#    #+#             */
/*   Updated: 2020/10/29 17:51:18 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_arg_exe_aux(t_shell *pcs, t_test *tst)
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
		free(join);
		exe = execve(join, pcs->cmp, g_envp);
		if (j == 3 && exe == -1 && !tst->check_pid)
		{
			dup2(pcs->std_out, 1);
			ft_putstr_fd(tst->error, 1);
			ft_putendl_fd(pcs->cmp[0], 1);
			ft_putstr_fd("\033[0m", 1);
			tst->status = 127;
			return (0);
		}
	}
	return (1);
}

int	ft_arg_exe(t_shell *pcs, t_test *tst, int i)
{
	char *aux;

	aux = ft_realloc_str(tst, pcs->pipesplit[i], -1, 1);
	ft_free_tab(pcs->cmp);
	if (pcs->pipesplit[i][0] == '\"' || pcs->pipesplit[i][0] == '\'')
		pcs->cmp = ft_split(pcs->pipesplit[i], '\"' | '\'');
	else
		pcs->cmp = ft_split_cmd(aux, ' ');
	if (!ft_arg_exe_aux(pcs, tst))
		return (127);
	return (0);
}
