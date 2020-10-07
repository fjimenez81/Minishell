/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 12:33:08 by fernando          #+#    #+#             */
/*   Updated: 2020/10/07 20:11:02 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_var_notequal(char *vars)
{
	int		i;
	char	*split;
	char	*copy;
	char	*aux;

	aux = ft_cut_end(vars, 1);
	split = ft_strjoin(aux, "=");
	free(aux);
	i = -1;
	while (g_envp[++i])
	{
		if ((copy = ft_strstr(g_envp[i], split)))
		{
			free(vars);
			vars = ft_strdup("");
		}
	}
	free(split);
}

static void	ft_change_var(char *vars)
{
	int		i;
	char	*split;
	char	*copy;
	char	*aux;

	if (ft_strchr(vars, '='))
	{
		aux = ft_cut_end(vars, 1);
		split = ft_strjoin(aux, "=");
		free(aux);
		i = -1;
		while (g_envp[++i])
		{
			if ((copy = ft_strstr(g_envp[i], split)))
				ft_memmove(g_envp[i], "", ft_strlen(g_envp[i]));
			else if ((copy = ft_strstr(g_envp[i], aux)) &&
				!ft_strchr(g_envp[i], '='))
				ft_memmove(g_envp[i], "", ft_strlen(g_envp[i]));
		}
		free(split);
	}
	else
		ft_var_notequal(vars);
}

static char	**ft_join_env(t_test *tst, int j)
{
	int		i;
	char	*aux;
	char	**res;

	aux = ft_strdup(ft_realloc_str(tst, tst->var_exp[j], -1, 0));
	ft_change_var(aux);
	if (aux[0] == '=')
	{
		ft_putendl_fd("[Minishell] ~> not found", 1);
		free(aux);
		return (g_envp);
	}
	if (!(res = (char **)malloc(sizeof(char*) * (tst->len_env + 2))))
		return (NULL);
	i = -1;
	while (g_envp[++i])
		res[i] = ft_strdup(g_envp[i]);
	res[i] = ft_strdup(aux);
	i++;
	res[i] = NULL;
	ft_free_tab(g_envp);
	free(aux);
	return (res);
}

int			ft_arg_export(t_test *tst, t_shell *pcs, int j)
{
	int i;

	tst->aux = ft_pass_space(pcs, pcs->pipesplit[j]);
	tst->var_exp = ft_split_cmd(tst->aux, ' ');
	if (ft_len_tab(tst->var_exp) == 1)
		ft_sort_export();
	else if (ft_len_tab(tst->var_exp) > 1)
	{
		ft_check_var_loop(tst);
		i = 0;
		while (tst->var_exp[++i])
		{
			if (!ft_strcmp(tst->var_exp[i], "") &&
				i < ft_len_tab(tst->var_exp) - 1)
				i++;
			g_envp = ft_join_env(tst, i);
		}
	}
	free(tst->aux);
	ft_free_tab(tst->var_exp);
	return (1);
}
