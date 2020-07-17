/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2arg_2echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <fjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 18:07:07 by fjimenez          #+#    #+#             */
/*   Updated: 2020/07/17 21:28:49 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_arg_echo_two(char *cmd, char **vars, int args)
{
	int i;
    int fspace;
    int write;
	int quotes;
    char *aux;
	char *dollar;
	char *var;

	i = 0;
    g_bool = 0;
    if (args)
    {
        if (vars[1] == NULL)
            return (1);
        else if (vars[1])
        {
            cmd = ft_cutstr(cmd, "echo", ft_strlen(cmd));
            fspace = 1;
            write = 0;
			quotes = 0;
            while (*cmd)
            {
                if ((*cmd == ' ' && *(cmd - 1) != '\\') && (fspace == 1 && write == 0))  
                    cmd++;
				if (((*cmd == '\"' || *cmd == '\'')&& *(cmd - 1) != '\\') && quotes == 0)
				{
					quotes = 1;
					write = 1;
					cmd++;
				}
				else if (((*cmd == '\"' || *cmd == '\'')&& *(cmd - 1) != '\\') && quotes == 1)
				{
					quotes = 0;
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
				else if ((*cmd == ' ' && *(cmd + 1) == ' ' && *(cmd - 1) != '\\') && (write == 1 && quotes == 0))
				{
					ft_putchar_fd(*cmd, 1);
					while (ft_isspace(*cmd))
						cmd += 1;
				}
				if ((*cmd == '$' && *(cmd + 1) != ' ') && quotes == 0)
				{
					dollar = ft_cut_end(cmd);
					aux = ft_strrchr(dollar, '$') + 1;
					i = -1;
					while (g_envp[++i])
					{
						var = ft_strstr(g_envp[i], aux);
						if (var != NULL)
							var = ft_strrchr(g_envp[i], '=') + 1;
						else
							var = ft_strdup("");	
					}
					ft_putstr_fd(var, 1);
					cmd += ft_strlen(dollar);
					if (ft_strlen(var) == 0)
						free(var);
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