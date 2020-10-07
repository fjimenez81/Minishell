/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 20:14:59 by fernando          #+#    #+#             */
/*   Updated: 2020/10/07 18:40:36 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*ft_strstr(char *str, char *to_find)
{
	int i;
	int j;

	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while (to_find[j] == str[i + j])
		{
			if (to_find[j + 1] == '\0')
				return (str + i);
			j++;
		}
		i++;
	}
	return (0);
}

static void	ft_unset_aux(char **aux, int i, int j)
{
	char	*unset;
	char	*tmp;
	char	**split;

	if (ft_strchr(aux[j], '='))
	{
		tmp = ft_strjoin(aux[j], "=");
		split = ft_split(g_envp[i], '=');
		unset = ft_strstr(g_envp[i], tmp);
	}
	else
	{
		split = ft_split(g_envp[i], '=');
		unset = ft_strstr(g_envp[i], aux[j]);
	}
	if (unset != NULL)
	{
		if (!ft_strcmp(split[0], aux[j]))
			ft_memmove(g_envp[i], "", ft_strlen(g_envp[i]));
	}
	if (ft_strchr(aux[j], '='))
		free(tmp);
	ft_free_tab(split);
}

static void	ft_check_unset(t_test *tst, t_shell *pcs)
{
	int i;
	int j;

	i = -1;
	while (g_envp[++i])
	{
		j = 0;
		while (++j < pcs->args)
		{
			if (!ft_strchr(pcs->cmp[j], '='))
				ft_unset_aux(pcs->cmp, i, j);
			else
			{
				ft_putstr_fd("unset: ", 1);
				ft_putstr_fd(pcs->cmp[j], 1);
				ft_putendl_fd(": invalid parameter name", 1);
				tst->status = 1;
				return ;
			}
		}
	}
}

void		ft_arg_unset(t_test *tst, t_shell *pcs)
{
	if (pcs->args == 1)
	{
		ft_putendl_fd("unset: not enough arguments", 1);
		tst->status = 1;
	}
	else if (pcs->args > 1)
		ft_check_unset(tst, pcs);
}
