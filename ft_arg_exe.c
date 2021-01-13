/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_exe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 17:23:10 by fjimenez          #+#    #+#             */
/*   Updated: 2021/01/13 11:43:46 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	ft_check_path(int *check)
// {
// 	int		k;

// 	k = -1;
// 	*check = 0;
// 	while (g_envp[++k])
// 	{
// 		if (ft_strstr(g_envp[k], "/usr/bin:") ||
// 			ft_strstr(g_envp[k], "/bin:"))
// 			*check = 1;
// 	}
// }

// static	int	ft_path(int j)
// {
// 	int i;
// 	int check;

// 	i = -1;
// 	if (j == 3)
// 		return (1);
// 	while (g_envp[++i])
// 	{
// 		if (ft_strstr(g_envp[i], "PATH="))
// 		{
// 			check = 1;
// 			if (ft_strrchr(g_envp[i], '=') + 1)
// 				ft_check_path(&check);
// 			return (check);
// 		}
// 	}
// 	return (0);
// }

void		ft_print_error(char *error)
{
	ft_putstr_fd("\033[1;31m[Minishell]: ", 1);
	ft_putstr_fd(error, 1);
	ft_putendl_fd(": command not found", 1);
}

char	**ft_path_split(void)
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

char **ft_add_str(char **s)
{
	int i;
	char **aux;

	if (!s || (!(aux = (char**)malloc(sizeof(char*) * (ft_len_tab(s) + 2)))))
		return (NULL);
	i = -1;
	while(s[++i])
		aux[i] = ft_join_char(s[i], '/');
	aux[i] = ft_strdup("");
	i++;
	aux[i] = NULL;
	ft_free_tab(s);
	return (aux);
}

void ft_exe_path(t_shell *pcs, t_test *tst, int i, char **aux)
{
	int		exe;

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

void ft_exe_cmd(t_shell *pcs, t_test *tst, int i, char **aux)
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

static void	ft_arg_exe_aux(t_shell *pcs, t_test *tst, int i)
{
	
	char	**aux;
	
	aux = ft_path_split();
	if (aux == NULL)
		ft_exe_path(pcs, tst, i, aux);
	else
		ft_exe_cmd(pcs, tst, i, aux);
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
