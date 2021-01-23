/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 18:07:07 by fjimenez          #+#    #+#             */
/*   Updated: 2021/01/22 21:22:48 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_first_ap(const char *s, int c)
{
	char *first;

	first = NULL;
	if (*s == c)
		return (char*)s;
	while (*s++)
	{
		if (*s == c)
		{
			first = (char*)s;
			break ;
		}
	}
	if (first)
		return (first);
	if (c == '\0')
		return ((char*)s);
	return (0);
}

static char	*ft_print_var_aux(char *var, char **tmp, int i)
{
	char *cut;

	cut = ft_cut_end(var, 0);
	if (!ft_strcmp(cut, tmp[0]))
	{
		var = ft_first_ap(g_envp[i], '=') + 1;
		free(cut);
		return (var);
	}
	else
		var = "";
	free(cut);
	return (var);
}

char		*ft_print_var(char *aux)
{
	int		i;
	char	*var;
	char	**tmp;

	i = -1;
	while (g_envp[++i])
	{
		tmp = ft_split(g_envp[i], '=');
		var = ft_strstr(g_envp[i], aux);
		if (var != NULL)
		{
			var = ft_print_var_aux(var, tmp, i);
			if (ft_strlen(var) > 0)
			{
				ft_free_tab(tmp);
				break ;
			}
		}
		else
			var = "";
		ft_free_tab(tmp);
	}
	return (var);
}

static int	ft_check_n(char *s)
{
	int i;

	i = -1;
	if (!ft_strcmp(s, ""))
		return (0);
	while (s[++i])
	{
		if (i == 0 && s[i] == '-' && s[i + 1] == '-')
			return (0);
		if (i == 0 && s[i] == 'n')
			return (0);
		if (s[i] == '-' && s[i + 1] == 'n')
			i++;
		if (s[i] == 'n' && s[i + 1] == '-')
			i++;
		if (s[i] != 'n')
			return (0);
	}
	return (1);
}

char	*ft_quit_n(char *s)
{
	int i;
	int j;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '-' && s[i + 1] == 'n')
		{
			i++;
			j = 0;
			while (s[i] == 'n')
			{
				j++;
				i++;
			}
			if (s[i] != 'n' && s[i] != 34 && s[i] != 39 && s[i] != ' ')
				return (s + i - j - 1);
			
		}
		if (s[i] != 'n' && s[i] != 34 && s[i] != 39 && s[i] != ' ')
			break ;
	}
	return (s + i);
}

static void	ft_echo_aux(t_shell *pcs, t_test *tst, int i)
{
	char *cmd;
	char *aux;
	char *tmp;

	cmd = ft_cutstr(pcs->pipesplit[i], "echo");
	tmp = ft_realloc_str(tst, pcs->cmp[1], -1, 0);
	if (ft_check_n(tmp))
	 	cmd = ft_quit_n(cmd);
	if (g_minish->exit == 130)
		aux = ft_realloc_str(tst, cmd, -1, 5);
	else if (tst->cheat)
		aux = ft_realloc_str(tst, cmd, -1, 9);
	else
		aux = ft_realloc_str(tst, cmd, -1, 0);
	ft_putstr_fd(aux, 1);
	if (!ft_check_n(tmp))
		ft_putchar_fd('\n', 1);
	free(aux);
	free(tmp);
}

int			ft_arg_echo(t_shell *pcs, t_test *tst, int i)
{
	if (pcs->args > 1)
	{
		if (pcs->cmp[1] == NULL)
			return (1);
		else if (pcs->cmp[1])
			ft_echo_aux(pcs, tst, i);
		return (0);
	}
	else
	{
		ft_putchar_fd('\n', 1);
		return (0);
	}
	return (1);
}
