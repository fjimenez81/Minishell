/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2arg_2echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <fjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 18:07:07 by fjimenez          #+#    #+#             */
/*   Updated: 2020/07/19 21:35:29 by fjimenez         ###   ########.fr       */
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
	char *cut;
	char **tmp;

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
					if (dollar != NULL)
					{
						aux = ft_strjoin(ft_strrchr(dollar, '$') + 1, "=");
						i = -1;
						while (g_envp[++i])
						{
							tmp = ft_split(g_envp[i], '=');
							var = ft_strstr(g_envp[i], aux);
							if (var != NULL)
							{
								cut = ft_cut_end(var);
								if (!ft_strcmp(cut, tmp[0]))
								{
									var = ft_strrchr(g_envp[i], '=') + 1;
									ft_free_tab(tmp);
									break ;
								}
								else
									var = "";
							}
							else
								var = "";
							ft_free_tab(tmp);
						}
						ft_putstr_fd(var, 1);
						cmd += ft_strlen(dollar);
						if (ft_strlen(cut) > 0)
							free(cut);
						free(aux);
						free(dollar);
					}
					else
					{
						while (*cmd != ' ')
							cmd++;
						cmd++;
					}
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