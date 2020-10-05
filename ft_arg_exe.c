/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_exe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <fjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 17:23:10 by fjimenez          #+#    #+#             */
/*   Updated: 2020/10/05 17:23:44 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_arg_exe(t_shell *pcs, t_test *tst, int i)
{
	char	*join;
	int		exe;
	int		j;

	exe = -1;
	j = 0;
	ft_free_tab(pcs->cmp);
	pcs->cmp = ft_split_cmd(ft_realloc_str
		(tst, pcs->pipesplit[i], -1, 1), ' ');
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
			exit(tst->status);
		}
	}
}
