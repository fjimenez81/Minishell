/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 20:14:59 by fernando          #+#    #+#             */
/*   Updated: 2021/01/23 13:46:11 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*ft_strstr(char *str, char *to_find)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (to_find[j] == str[i])
	{
		if (to_find[j + 1] == 0)
			return (str);
		j++;
		i++;
	}
	return (0);
}

static void	ft_unset_aux(t_test *t)
{
	char	*unset;
	char	*tmp;
	char	**split;

	tmp = ft_strjoin(t->aux, "=");
	if (ft_strchr(t->aux, '='))
	{
		split = ft_split(g_envp[t->k], '=');
		unset = ft_strstr(g_envp[t->k], tmp);
	}
	else
	{
		split = ft_split(g_envp[t->k], '=');
		unset = ft_strstr(g_envp[t->k], t->aux);
	}
	if (unset != NULL)
	{
		if (!ft_strcmp(split[0], t->aux))
			ft_memmove(g_envp[t->k], "", ft_strlen(g_envp[t->k]));
	}
	free(tmp);
	ft_free_tab(split);
}

static void	ft_loop_unset(t_test *t, t_shell *pcs, int j, int i)
{
	t->aux = ft_realloc_str(t, pcs->cmp[j], -1, 0);
	if (!ft_strchr(pcs->cmp[j], '=') && i == pcs->n_pipe - 1 &&
		ft_strlen(t->aux))
		ft_unset_aux(t);
	else if ((ft_strchr(pcs->cmp[j], '=') || !ft_strlen(t->aux)) && !t->bool2)
	{
		ft_putstr_fd("\033[1;31m[Minishell]: unset: `", 1);
		ft_putstr_fd(t->aux, 1);
		ft_putendl_fd("\': not a valid identifier", 1);
		t->bool2 = 1;
		t->status = 1;
	}
	free(t->aux);
}

void		ft_arg_unset(t_shell *pcs, t_test *t, int i)
{
	int j;

	t->k = -1;
	t->bool2 = 0;
	ft_free_tab(pcs->cmp);
	pcs->cmp = ft_split_cmd(pcs->pipesplit[i], ' ');
	while (g_envp[++t->k])
	{
		j = 0;
		while (++j < ft_len_tab(pcs->cmp))
			ft_loop_unset(t, pcs, j, i);
	}
}
