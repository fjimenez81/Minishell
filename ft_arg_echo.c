/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <fjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 18:07:07 by fjimenez          #+#    #+#             */
/*   Updated: 2020/09/12 17:15:15 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *ft_print_var_aux(char *var, char **tmp, int i)
{
	char *cut;

	cut = ft_cut_end(var);
	if (!ft_strcmp(cut, tmp[0]))
	{
		var = ft_strrchr(g_envp[i], '=') + 1;
		free(cut);
		return (var);
	}
	else
		var = "";
	free(cut);
	return (var);
}

char *ft_print_var(char *aux)
{
	int i;
	char *var;
	char **tmp;

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

int ft_arg_echo(t_shell *pcs, t_test *tst, int i)
{
	char *cmd;
    char *aux;
	
    if (pcs->args)
    {
        if (pcs->cmp[1] == NULL)
            return (1);
        else if (pcs->cmp[1])
        {
            cmd = ft_cutstr(pcs->pipesplit[i], "echo");
			if (!ft_strcmp(pcs->cmp[1], "-n"))
				cmd = ft_cutstr(cmd, "-n");
			aux = ft_realloc_str(tst, cmd, -1, 0);
			ft_putstr_fd(aux, 1);
        	if (ft_strcmp(pcs->cmp[1], "-n"))
				ft_putchar_fd('\n', 1);
        }
        return (1);
    }
    return (0);
}