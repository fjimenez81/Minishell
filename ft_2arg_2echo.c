/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2arg_2echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <fjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 18:07:07 by fjimenez          #+#    #+#             */
/*   Updated: 2020/07/22 20:54:23 by fjimenez         ###   ########.fr       */
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

int ft_arg_echo_two(char *cmd, char **vars, int args)
{
	int i;
    int fspace;
    int write;
	int quotes;
    char *aux;
	char *dollar;

	i = 0;
    if (args)
    {
        if (vars[1] == NULL)
            return (1);
        else if (vars[1])
        {
            cmd = ft_cutstr(cmd, "echo", ft_strlen(cmd));
			i = -1;
			quotes = 0;
			fspace = 1;
			write = 0;
			quotes = 0;
			while (*cmd)
			{
				if ((*cmd == ' ' && *(cmd - 1) != '\\') &&
					(fspace == 1 && write == 0)) 
					cmd++;
				if (((*cmd == '\"' || *cmd == '\'')&& *(cmd - 1) != '\\')
					&& quotes == 0)
				{
					quotes = 1;
					write = 1;
					cmd++;
				}
				else if (((*cmd == '\"' || *cmd == '\'') &&
					*(cmd - 1) != '\\') && quotes == 1)
				{
					quotes = 0;
					cmd++;
				}
				else if ((*cmd == '\\' && (*(cmd + 1) == '\"' ||
					*(cmd + 1) == '\'')) && quotes == 1)
				{
					cmd++;
					ft_putchar_fd(*cmd, 1);
					cmd++;
				}
				else if ((*cmd == '\\' && *(cmd + 1) == ' ') && quotes == 0)
				{
					fspace = 0;
					write = 1;
					cmd++;
					ft_putchar_fd(*cmd, 1);
					cmd++;
				}
				else if ((*cmd == ' ' && *(cmd + 1) == ' ' &&
					*(cmd - 1) != '\\') && (write == 1 && quotes == 0))
				{
					ft_putchar_fd(*cmd, 1);
					while (ft_isspace(*cmd))
						cmd += 1;
				}
				else if ((*cmd == '$' && *(cmd + 1) != ' ' &&
					*(cmd + 1) != '\0') && quotes == 0)
				{
					dollar = ft_cut_end(cmd);
					aux = ft_strjoin(ft_strrchr(dollar, '$') + 1, "=");
					ft_putstr_fd(ft_print_var(aux), 1);
					cmd += ft_strlen(dollar);
					free(aux);
					free(dollar);
				}
				else
				{
					write = 1;
					ft_putchar_fd(*cmd, 1);
					cmd++;
				}
			}
        	if (ft_strcmp(vars[1], "-n"))
				ft_putchar_fd('\n', 1);
        }
        return (1);
    }
    else
        return (0);
    return (-1);
}