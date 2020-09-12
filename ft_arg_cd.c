/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <fjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 21:08:07 by fernando          #+#    #+#             */
/*   Updated: 2020/09/12 17:22:55 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ft_get_up_var(char *oldpath)
{
	char path[PATH_MAX];
	char *aux;
	int i;
	int pos;

	getcwd(path, -1);
	i = -1;
	aux = ft_strjoin("PWD=", oldpath);
	pos = 0;
	while (g_envp[++i])
	{
		if (ft_strstr(g_envp[i], "OLD"))
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

static char *ft_get_var(char *str)
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

static void ft_cd_two_arg(t_shell *pcs, char *oldpath)
{
	t_test tmp;

	if (pcs->args == 1 || !ft_strcmp(pcs->cmp[0], "~"))
	{
        if (chdir(ft_get_var("HOME")) == 0)
			ft_get_up_var(oldpath);
	}
	else if (pcs->args == 2 && chdir(ft_realloc_str(&tmp, pcs->cmp[1], -1, 0)) == 0)
		ft_get_up_var(oldpath);
}

int ft_arg_cd(t_shell *pcs)
{
	char oldpath[PATH_MAX];

	getcwd(oldpath, -1);
    if (pcs->args > 2)
    {
        ft_putstr_fd("cd: too many arguments\n", 1);
        return (0);
    }
	else if (pcs->args == 2 && !ft_strcmp(pcs->cmp[1], ".."))
    {
        chdir("..");
		getcwd(oldpath, -1);
		return (1);
    }
    else if (pcs->args <= 2)
    {
		ft_cd_two_arg(pcs, oldpath);
		return (1);
    }
    ft_putstr_fd("Error: No such file or directory\n", 1);
    return(0);
}