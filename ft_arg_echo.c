/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernando <fernando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 15:26:37 by fernando          #+#    #+#             */
/*   Updated: 2020/03/27 14:41:59 by fernando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *ft_echo_aux(char *vars)
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
	//free(vars);
	//free(aux);
    return (tmp);
}

int ft_arg_echo(char *command, char **vars, int args)
{
    char *aux;
    char *tmp;
	char *tmp2;
	//char *tmp3;

    
    if (args)
    {
        if (!ft_strcmp(vars[1], "-n"))
        {
            if (vars[2])
            {
                tmp = ft_strtrim(command, "echo");
                tmp2 = ft_strtrim(tmp, " \t-n");
                aux = ft_echo_aux(tmp2);
                ft_putendl_fd(ft_strdup(aux), 1);
            }
            else
                return (0);
        }
        else if (ft_strcmp(vars[1], "-n") != 0)
        {
            tmp = ft_strtrim(command, "echo");
            tmp2 = ft_strtrim(tmp, " \t");
            aux = ft_echo_aux(tmp2);
            ft_putendl_fd(aux, 1);
			ft_str_free(vars);
			free(tmp);
			free(aux);
			//free(tmp2);
        }
        return (1);
    }
    else
    {
        return (0);
    }
    return (-1);
}