/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 21:08:07 by fernando          #+#    #+#             */
/*   Updated: 2020/12/16 15:56:33 by fjimenez         ###   ########.fr       */
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

static char	*ft_get_var(char *str)
{
	int i;

	i = -1;
	while (g_envp[++i])
	{
		if (ft_strstr(g_envp[i], str))
			return (ft_strnstr(g_envp[i], "=", ft_strlen(g_envp[i])) + 1);
	}
	return (NULL);
}

int			ft_arg_cd(t_shell *pcs, t_test *tst)
{
	char	oldpath[PATH_MAX];
	char	*aux;

	getcwd(oldpath, -1);
	if (pcs->args == 1 || !ft_strcmp(pcs->cmp[0], "~"))
	{
		if (chdir(ft_get_var("HOME")) == 0)
			ft_get_up_var(oldpath);
		return (1);
	}
	aux = ft_realloc_str(tst, pcs->cmp[1], -1, 0);
	if (chdir(aux) == 0)
		ft_get_up_var(oldpath);
	else
	{
		ft_putstr_fd("\033[1;31m[Minishell]: cd: ", 1);
		ft_putstr_fd(pcs->cmp[1], 1);
		ft_putendl_fd(": No such file or directory", 1);
		tst->status = 1;
	}
	free(aux);
	return (1);
}
