/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exp_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 15:28:04 by fjimenez          #+#    #+#             */
/*   Updated: 2020/10/07 18:31:24 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_sort_export_aux(char **export, int len)
{
	int i;
	int j;

	i = -1;
	while (++i < (len - 1))
	{
		j = i + 1;
		while (j < len - 1)
		{
			if (ft_strcmp(export[i], export[j]) > 0)
				ft_swap(&export[i], &export[j]);
			j++;
		}
	}
	return (export);
}

static void	ft_print_export(char **export, int i)
{
	char *tmp;

	if (ft_strchr(export[i], '=') &&
		export[i][ft_strlen(export[i]) - 1] == '=')
	{
		tmp = export[i];
		free(export[i]);
		export[i] = ft_strjoin(tmp, "\'\'");
		ft_putendl_fd(export[i], 1);
	}
	else if (ft_strcmp(export[i], "") != 0 && ft_strchr(export[i], '='))
		ft_putendl_fd(export[i], 1);
	else if (!ft_strchr(export[i], '=') && ft_strcmp(export[i], "") != 0)
	{
		tmp = export[i];
		free(export[i]);
		export[i] = ft_strjoin(tmp, "=''");
		ft_putendl_fd(export[i], 1);
	}
}

void		ft_sort_export(void)
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
		ft_print_export(export, i);
	ft_free_tab(export);
}
