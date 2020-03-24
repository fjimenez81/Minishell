/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernando <fernando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 15:26:37 by fernando          #+#    #+#             */
/*   Updated: 2020/03/24 20:28:52 by fernando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *ft_echo_aux(char *args)
{
    char *tmp;
    char **aux;
    int len;
    int i;
    
    len = ft_strlen(args) - 1;
    i = 0;
    while (args[i])
    {
        if (args[i] == '\"' && args[len] == '\"')
            aux =ft_split(args, '\"');
        else if (args[i] == '\'' && args[len] == '\'')
            aux =ft_split(args, '\'');
        else if ((args[i] == '\'' && args[i + len] == '\"') ||
            (args[i] == '\"' && args[i + len] == '\''))
            return (NULL);
        else
            aux = &args;
        tmp = aux[0];
        i++;
    }
    return (tmp);
}

int ft_arg_echo(char **args, int command)
{
    char *aux;

    if (command)
    {
        if (!ft_strcmp(args[1], "-n"))
        {
            if (args[2])
            {
                aux = ft_echo_aux(args[2]);
                ft_putstr_fd(ft_strdup(aux), 1);
            }
            else
                return (0);
        }
        else if (ft_strcmp(args[1], "-n") != 0)
        {
            aux = ft_echo_aux(args[1]);
            ft_putstr_fd(aux, 1);
        }
        return (1);
    }
    else
    {
        return (0);
    }
    return (-1);
}