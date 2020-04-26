/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernando <fernando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 15:26:37 by fernando          #+#    #+#             */
/*   Updated: 2020/04/26 22:02:54 by fernando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static char *ft_echo_aux(char *vars)
{
    char *tmp;
    char **aux;
    int len;
    int i;
    
    len = ft_strlen(vars) - 1;
    i = 0;
    while (vars[i])
    {
        if (vars[i] == '\"' && vars[len] == '\"')
            aux = ft_str_tok(vars, "\"");
        else if (vars[i] == '\'' && vars[len] == '\'')
            aux = ft_str_tok(vars, "\'");
        else if ((vars[i] == '\'' && vars[i + len] == '\"') ||
            	(vars[i] == '\"' && vars[i + len] == '\''))
				return (NULL);
        else
            aux = &vars;
        tmp = aux[0];
        i++;
    }
    return (tmp);
}*/

int ft_arg_echo(char *command, char **vars, int args)
{
    char *tmp;
    char *aux;
    char **split;
    int len;
	int i;
    int j;

	i = 0;
    ignore_space(&command);
    len = ft_len_tab(vars);
    if (args)
    {
        if (vars[1] == NULL)
            return (1);
        else if (!ft_strcmp(vars[1], "-n"))
        {
            if (vars[2])
            {
				command = ft_strtrim(command, "echo");
				tmp = ft_strtrim(command, " \t\a\r-n");
				while (tmp[i])
				{
					if (tmp[i] == '\"' || tmp[i] == '\'')
						i++;
					ft_putchar_fd(tmp[i++], 1);
				}
				free(command);
				free(tmp);
            }
            else
                return (0);
        }
        else if (ft_strcmp(vars[1], "-n") != 0)
        {
            command = ft_strtrim(command, "echo");
			tmp = ft_strtrim(command, " \t\a\r");
            if (ft_strchr(tmp, '$'))
            {
                i = -1;
                aux = ft_strtrim(tmp, "$");
                while (g_envp[++i])
                {
                    j = 0;
                    while (++j < len)
                    {
                        free(tmp);
                        tmp = ft_strstr(g_envp[i], aux);
                    }
                }
            }
            i = 0;
			while (tmp[i])
			{
				if (tmp[i] == '\"' || tmp[i] == '\'')
					i++;
				ft_putchar_fd(tmp[i++], 1);
			}
            ft_putchar_fd('\n', 1);
			free(tmp);
            free(aux);
			free(command);
        }
        return (1);
    }
    else
    {
        return (0);
    }
    return (-1);
}