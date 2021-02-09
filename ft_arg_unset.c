/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 20:14:59 by fernando          #+#    #+#             */
/*   Updated: 2021/02/07 17:38:47 by fjimenez         ###   ########.fr       */
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
	split = ft_split(g_envp[t->k], '=');
	if (ft_strchr(t->aux, '='))
		unset = ft_strstr(g_envp[t->k], tmp);
	else
		unset = ft_strstr(g_envp[t->k], t->aux);
	if (unset != NULL)
	{
		if (!ft_strcmp(split[0], t->aux))
			ft_memmove(g_envp[t->k], " ", ft_strlen(g_envp[t->k]));
	}
	free(tmp);
	ft_free_tab(split);
}

static int	ft_unset_check(char *s)
{
	int i;

	i = -1;
	while (s[++i])
	{
		if (i == 0 && ft_isdigit(s[i]))
			return (0);
		if (s[i] == 92)
			i++;
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
	}
	return (1);
}

static void	ft_loop_unset(t_test *t, t_shell *pcs, int j)
{
	t->aux = ft_realloc_str(pcs->cmp[j], -1, 0);
	if (ft_unset_check(t->aux) && ft_strlen(t->aux))
		ft_unset_aux(t);
	else if ((!ft_unset_check(t->aux) ||
			!ft_strlen(t->aux)) && !t->bool2)
	{
		ft_print_error(t->aux, "unset: `", "\': not a valid identifier");
		t->bool2 = 1;
		pcs->ret = 1;
	}
	free(t->aux);
}

int			ft_arg_unset(t_shell *p)
{
	int		j;
	t_test	t;

	t.k = -1;
	t.bool2 = 0;
	p->ret = 0;
	ft_free_tab(p->cmp);
	p->cmp = ft_split_cmd(p->pipesplit[p->n], ' ');
	while (g_envp[++t.k])
	{
		j = 0;
		while (++j < ft_len_tab(p->cmp))
			ft_loop_unset(&t, p, j);
	}
	return (p->ret);
}
