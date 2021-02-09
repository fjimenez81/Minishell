/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 12:33:08 by fernando          #+#    #+#             */
/*   Updated: 2021/02/08 20:58:15 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_change_var_aux(char *vars, char *aux, char *split, int i)
{
	char	*tmp;

	if (!ft_strncmp(g_envp[i], aux, ft_strlen(aux)) &&
			ft_strchr(vars, '='))
	{
		tmp = ft_strjoin(split, ft_first_ap(vars, '=') + 1);
		free(g_envp[i]);
		g_envp[i] = tmp;
		free(aux);
		free(split);
		return (0);
	}
	if (!ft_strncmp(g_envp[i], aux, ft_strlen(aux)) &&
		ft_strchr(g_envp[i], '=') && !ft_strchr(vars, '='))
	{
		free(aux);
		free(split);
		return (0);
	}
	return (1);
}

static int	ft_change_var(char *vars, int i)
{
	char	*split;
	char	*aux;

	aux = ft_cut_end(vars, 1);
	split = ft_strjoin(aux, "=");
	while (g_envp[++i])
		if (!ft_change_var_aux(vars, aux, split, i))
			return (0);
	free(split);
	free(aux);
	return (1);
}

static char	**ft_join_env(t_test *tst, int j)
{
	int		i;
	char	*aux;
	char	**res;

	aux = ft_realloc_str(tst->var_exp[j], -1, 0);
	if (!ft_change_var(aux, -1))
	{
		free(aux);
		return (g_envp);
	}
	if (!(res = (char **)malloc(sizeof(char*) * (ft_len_tab(g_envp) + 2))))
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

static void	ft_arg_export_aux(t_shell *p, t_test *t)
{
	char	*aux;
	int		len;

	t->bool = 0;
	t->bool2 = 0;
	t->var_exp = ft_split_cmd(p->pipesplit[p->n], ' ');
	len = ft_len_tab(t->var_exp);
	if (len == 2)
		aux = ft_realloc_str(t->var_exp[1], -1, 0);
	if ((len == 2 && !ft_strlen(aux) && (ft_strcmp(t->var_exp[1], "\"\"") &&
		ft_strcmp(t->var_exp[1], "\'\'"))) || len == 1)
	{
		t->bool2 = 1;
		ft_sort_export(p->fd);
	}
	if (len == 2)
		free(aux);
}

int			ft_arg_export(t_shell *p)
{
	int		i;
	t_test	t;

	p->ret = 0;
	ft_arg_export_aux(p, &t);
	if (ft_len_tab(t.var_exp) > 1 && !t.bool2)
	{
		ft_check_var_loop(p, &t, 0);
		i = 0;
		if (!t.bool)
		{
			while (t.var_exp[++i])
				if (ft_strcmp(t.var_exp[i], "") != 0)
					g_envp = ft_join_env(&t, i);
		}
	}
	ft_free_tab(t.var_exp);
	return (p->ret);
}
