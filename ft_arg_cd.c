/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 21:08:07 by fernando          #+#    #+#             */
/*   Updated: 2021/02/08 11:26:21 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_get_up_var(void)
{
	char	path[PATH_MAX];
	int		i;
	int		pos;
	int		j;

	getcwd(path, -1);
	i = -1;
	pos = 0;
	j = 0;
	while (g_envp[++i])
	{
		if (!ft_strncmp(g_envp[i], "OLDPWD=", 7))
			pos = i;
		else if (!ft_strncmp(g_envp[i], "PWD=", 4))
			j = i;
	}
	free(g_envp[pos]);
	g_envp[pos] = ft_strjoin("OLDPWD=", ft_first_ap(g_envp[j], '=') + 1);
	free(g_envp[j]);
	g_envp[j] = ft_strjoin("PWD=", path);
}

static int	ft_arg_cd_aux(t_test *t)
{
	if (!ft_strlen(t->aux))
		return (0);
	t->cd = chdir(t->aux);
	if (!t->cd)
	{
		ft_get_up_var();
		return (0);
	}
	ft_print_error(t->aux, "cd: ", ": No such file or directory");
	return (1);
}

int			ft_arg_cd(t_shell *pcs)
{
	char	oldpath[PATH_MAX];
	t_test	t;

	pcs->ret = 0;
	getcwd(oldpath, -1);
	if (pcs->args == 1)
	{
		t.aux = ft_get_var("HOME=", 1);
		if (t.aux == NULL)
			pcs->ret = 1;
		t.cd = chdir(t.aux);
		if (!t.cd)
			ft_get_up_var();
		free(t.aux);
		return (pcs->ret);
	}
	t.aux = pcs->cmp[1];
	return (ft_arg_cd_aux(&t));
}
