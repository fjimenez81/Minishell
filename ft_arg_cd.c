/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 21:08:07 by fernando          #+#    #+#             */
/*   Updated: 2021/01/21 07:39:23 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_get_up_var(char *oldpath)
{
	char	path[PATH_MAX];
	char	*aux;
	int		i;
	int		pos;

	getcwd(path, -1);
	i = -1;
	aux = ft_strjoin("PWD=", oldpath);
	pos = 0;
	while (g_envp[++i])
	{
		if (ft_strstr(g_envp[i], "OLDPWD="))
		{
			pos = i;
			i++;
		}
		else if (ft_strstr(g_envp[i], aux))
			break ;
	}
	free(aux);
	free(g_envp[i]);
	g_envp[i] = ft_strjoin("PWD=", path);
	free(g_envp[pos]);
	g_envp[pos] = ft_strjoin("OLDPWD=", oldpath);
}

char		*ft_get_var(t_test *t, char *path, int find)
{
	int i;

	i = -1;
	t->aux = NULL;
	while (g_envp[++i])
	{
		if (ft_strstr(g_envp[i], path))
		{
			t->aux = ft_strrchr(g_envp[i], '=') + 1;
			return (t->aux);
		}
	}
	if (!t->aux && find == 1)
	{
		ft_putendl_fd("\033[1;31m[Minishell]: cd: HOME not set", 1);
		t->status = 1;
	}
	return (NULL);
}

static void	ft_arg_cd_aux(t_shell *pcs, t_test *t, char *oldpath, int i)
{
	if (i == pcs->n_pipe - 1)
	{
		if (chdir(t->aux) == 0)
		{
			ft_get_up_var(oldpath);
			t->cd = 1;
		}
	}
	if (!t->cd)
	{
		if (chdir(t->aux) != 0)
		{
			ft_putstr_fd("\033[1;31m[Minishell]: cd: ", 1);
			ft_putstr_fd(t->aux, 1);
			ft_putendl_fd(": No such file or directory", 1);
			t->status = 1;
		}
		chdir(oldpath);
	}
}

void		ft_arg_cd(t_shell *pcs, t_test *t, int i)
{
	char	oldpath[PATH_MAX];

	getcwd(oldpath, -1);
	ft_free_tab(pcs->cmp);
	pcs->cmp = ft_split_cmd(pcs->pipesplit[i], ' ');
	if (!ft_only_path(pcs, t))
		return ;
	if (i == pcs->n_pipe - 1 && (ft_len_tab(pcs->cmp) == 1 ||
		!ft_strcmp(pcs->cmp[0], "~") || pcs->cmp[1][0] == '<' ||
		pcs->cmp[1][0] == '>'))
	{
		if (chdir(ft_get_var(t, "HOME", 1)) == 0)
			ft_get_up_var(oldpath);
		return ;
	}
	t->aux = ft_realloc_str(t, pcs->cmp[1], -1, 0);
	ft_arg_cd_aux(pcs, t, oldpath, i);
	free(t->aux);
}
