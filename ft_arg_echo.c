/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernando <fernando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 15:26:37 by fernando          #+#    #+#             */
/*   Updated: 2020/04/01 18:49:03 by fernando         ###   ########.fr       */
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
	int i;

    if (args)
    {
        if (!ft_strcmp(vars[1], "-n"))
        {
            if (vars[2])
            {
				command = ft_strtrim(command, "echo");
				tmp = ft_strtrim(command, " \t\a\r-n");
                i = 0;
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
			i = 0;
			while (tmp[i])
			{
				if (tmp[i] == '\"' || tmp[i] == '\'')
					i++;
				ft_putchar_fd(tmp[i++], 1);
			}
			free(tmp);
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