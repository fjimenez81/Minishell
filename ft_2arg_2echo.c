/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2arg_2echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <fjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 18:07:07 by fjimenez          #+#    #+#             */
/*   Updated: 2020/07/20 19:32:19 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_arg_echo_two(char *cmd, char **vars, int args)
{
	int i;
	int fdout;
	int fdin;
	int bool_redir;
    int fspace;
    int write;
	int quotes;
    char *aux;
	char *dollar;
	char *var;
	char *cut;
	char **tmp;
	char **redir;

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
			bool_redir = 0;
			while (cmd[++i])
			{
				if (((cmd[i] == '\"' || cmd[i] == '\'')&& cmd[i - 1] != '\\')
					&& quotes == 0)
				{
					quotes = 1;
					write = 1;
					cmd++;
				}
				else if (((cmd[i] == '\"' || cmd[i] == '\'') &&
					cmd[i - 1] != '\\') && quotes == 1)
				{
					quotes = 0;
					cmd++;
				}
				else if ((cmd[i] == '>' || cmd[i] == '<') && quotes == 0)
				{
					fdin = 0;
					if (cmd[i] == '>')
					{
						bool_redir = 1;
						redir = ft_split(cmd, '>');
						fdin = open(redir[0], O_RDWR);
						fdout = open(redir[1], O_TRUNC | O_RDWR | O_CREAT);
						close(0);
       					dup2(fdin, 0);
						ft_putstr_fd(redir[0], 0);
       					close(fdin);
       					close(1);
       					dup2(fdout, 1);
       					close(fdout);
						
						//0: stdin
						//1: stdout
						//2: stderr
					}
				}
			}
			if (bool_redir == 0)
			{
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
					else if ((*cmd == '$' && *(cmd + 1) != ' ') && quotes == 0)
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
										free(cut);
										break ;
									}
									else
										var = "";
									free(cut);
								}
								else
									var = "";
								ft_free_tab(tmp);
							}
							ft_putstr_fd(var, 1);
							cmd += ft_strlen(dollar);
							free(aux);
							free(dollar);
						}
						else
						{
							while (*cmd != ' ' && *cmd != '\0')
								cmd += 1;
						}
					}
					else
					{
						write = 1;
						ft_putchar_fd(*cmd, 1);
						cmd++;
					}
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