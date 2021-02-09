/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 18:07:07 by fjimenez          #+#    #+#             */
/*   Updated: 2021/02/09 16:34:40 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*ft_print_var(char *s)
{
	int		i;
	char	*var;
	char	**tmp;

	i = -1;
	while (g_envp[++i])
	{
		tmp = ft_split(g_envp[i], '=');
		if (!ft_strncmp(s, tmp[0], ft_strlen(tmp[0])))
		{
			var = ft_strstr(g_envp[i], s);
			if (var != NULL)
			{
				var = ft_first_ap(g_envp[i], '=') + 1;
				if (ft_strlen(var) > 0)
				{
					ft_free_tab(tmp);
					return (var);
				}
			}
		}
		ft_free_tab(tmp);
	}
	return ("");
}

static int	ft_echo_aux(t_shell *p)
{
	char	*cmd;
	char	*aux;
	char	**echo;
	int		i;

	cmd = ft_cutstr(p->pipesplit[p->n], "echo");
	if (ft_check_n(p->cmp[1]))
		cmd = ft_quit_n(cmd);
	echo = ft_split_cmd(cmd, ' ');
	i = -1;
	while (echo[++i])
	{
		aux = ft_realloc_str(echo[i], -1, 0);
		ft_putstr_fd(aux, p->fd);
		if (i < ft_len_tab(echo) - 1)
			ft_putchar_fd(' ', p->fd);
		free(aux);
	}
	if (!ft_check_n(p->cmp[1]))
		ft_putchar_fd('\n', p->fd);
	ft_free_tab(echo);
	return (0);
}

int			ft_arg_echo(t_shell *pcs)
{
	if (pcs->args > 1)
	{
		if (pcs->cmp[1] == NULL)
			return (1);
		else if ((pcs->cmp[1][0] == '-' && pcs->cmp[1][1] == 'n' &&
				!pcs->cmp[1][2] && !pcs->cmp[2]) || (pcs->cmp[1] &&
				!ft_echo_aux(pcs)))
			return (0);
		else
			return (1);
	}
	else
	{
		ft_putchar_fd('\n', 1);
		return (0);
	}
	return (0);
}
