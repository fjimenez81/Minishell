/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exp_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 15:28:04 by fjimenez          #+#    #+#             */
/*   Updated: 2021/02/02 13:04:38 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_pt_syntax_aux_three(t_test *t)
{
	if (t->aux[t->i] == '>' && t->aux[t->i + 1] == '>')
	{
		while (t->aux[t->i] == ' ')
			t->i++;
		if (t->aux[t->i] == '>' && t->aux[t->i + 1] == '>' &&
			t->aux[t->i + 2] != '>')
		{
			ft_putstr_fd("\033[1;31m[Minishell]: ", 1);
			ft_putendl_fd("syntax error near unexpected token `>'", 1);
			free(t->aux);
			return (0);
		}
		t->i++;
		if (t->aux[t->i] == '>' && t->aux[t->i + 1] == '>')
		{
			ft_putstr_fd("\033[1;31m[Minishell]: ", 1);
			ft_putendl_fd("syntax error near unexpected token `>>'", 1);
			free(t->aux);
			return (0);
		}
	}
	return (1);
}

static char	**ft_sort_export_aux(char **export, int len)
{
	int i;
	int j;

	i = -1;
	while (++i < (len - 1))
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strcmp(export[i], export[j]) > 0)
				ft_swap(&export[i], &export[j]);
			j++;
		}
	}
	return (export);
}

static void	ft_print_export(char **export, int i, int fd)
{
	int j;
	int bool;

	j = -1;
	bool = 0;
	while (export[i][++j])
	{
		if (export[i][j] == '=' && export[i][j + 1] != 0 && !bool)
		{
			ft_putstr_fd("=\"", fd);
			bool = 1;
		}
		else if (j == (int)ft_strlen(export[i]) - 1)
		{
			ft_putchar_fd(export[i][j], fd);
			if (ft_strchr(export[i], '='))
				ft_putchar_fd(34, fd);
			ft_putchar_fd('\n', fd);
		}
		else
			ft_putchar_fd(export[i][j], fd);
	}
}

void		ft_sort_export(int fd)
{
	int		i;
	int		len;
	char	**export;

	len = ft_len_tab(g_envp);
	if (!(export = (char**)malloc(sizeof(char*) * len + 1)))
		return ;
	i = -1;
	while (g_envp[++i])
		export[i] = ft_strdup(g_envp[i]);
	export[i] = NULL;
	export = ft_sort_export_aux(export, len);
	i = -1;
	while (export[++i])
	{
		len = 0;
		if (export[i][0] == '_' && export[i][1] == '=')
			len = 1;
		if (!len && export[i][0] != ' ')
		{
			ft_putstr_fd("declare -x ", fd);
			ft_print_export(export, i, fd);
		}
	}
	ft_free_tab(export);
}
