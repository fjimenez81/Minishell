/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 20:14:59 by fernando          #+#    #+#             */
/*   Updated: 2021/01/21 07:49:57 by fjimenez         ###   ########.fr       */
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
		if (to_find[j + 1] == '\0')
			return (str);
		j++;
		i++;
	}
	return (0);
}

static void	ft_unset_aux(t_test *t, char **aux, int j)
{
	char	*unset;
	char	*tmp;
	char	**split;

	tmp = ft_strjoin(aux[j], "=");
	if (ft_strchr(aux[j], '='))
	{
		split = ft_split(g_envp[t->k], '=');
		unset = ft_strstr(g_envp[t->k], tmp);
	}
	else
	{
		split = ft_split(g_envp[t->k], '=');
		unset = ft_strstr(g_envp[t->k], aux[j]);
	}
	if (unset != NULL)
	{
		if (!ft_strcmp(split[0], aux[j]))
			ft_memmove(g_envp[t->k], "", ft_strlen(g_envp[t->k]));
	}
	free(tmp);
	ft_free_tab(split);
}

void		ft_arg_unset(t_shell *pcs, t_test *t, int k)
{
	int j;

	t->k = -1;
	t->aux = ft_realloc_str(t, pcs->pipesplit[k], -1, 0);
	ft_free_tab(pcs->cmp);
	pcs->cmp = ft_split_cmd(t->aux, ' ');
	while (g_envp[++t->k])
	{
		j = 0;
		while (++j < ft_len_tab(pcs->cmp))
		{
			if (!ft_strchr(pcs->cmp[j], '=') && k == pcs->n_pipe - 1)
				ft_unset_aux(t, pcs->cmp, j);
			else if (ft_strchr(pcs->cmp[j], '='))
			{
				ft_putstr_fd("\033[1;31m[Minishell]: unset: `", 1);
				ft_putstr_fd(pcs->cmp[j], 1);
				ft_putendl_fd("\': not a valid identifier", 1);
				t->status = 1;
				free(t->aux);
				return ;
			}
		}
	}
	free(t->aux);
}
