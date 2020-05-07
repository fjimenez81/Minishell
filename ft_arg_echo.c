/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernando <fernando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 15:26:37 by fernando          #+#    #+#             */
/*   Updated: 2020/05/07 14:38:52 by fernando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_echo_var(char *tmp)
{
	int i;
	char *aux;

	i = -1;
    aux = ft_strrchr(tmp, '$') + 1;
    while (g_envp[++i])
    {
        tmp = ft_strstr(g_envp[i], aux);
        if (tmp != NULL)
			tmp = ft_strrchr(tmp, '=') + 1;
        else
            tmp = "";   
    }
    return (tmp);
}

static int ft_not_quote_aux(char *vars, char *command)
{
    int i;

    i = -1;
    while (command[++i])
    {
        if (command[i] == ' ')
            i++;
        if (command[i] == '$')
            break ;
         else
            ft_putchar_fd(command[i], 1); 
    }
    ft_putstr_fd(ft_echo_var(vars), 1);
    ft_putchar_fd(' ', 1);
    i += ft_strlen(vars) + i - 2;
    return (i);
}

int ft_not_quote(char *vars, char *command)
{
    int i;

    i = 0;
	if (ft_search_c(vars, '$'))
        i = ft_not_quote_aux(vars, command);
    else
    {
        while (*command)
        {
            if (*command == ' ')
                i++;
            if (*command != ' ' && *(command + 1) == ' ')
                break;
            command++;
        }
        ft_putstr_fd(vars, 1);
        ft_putchar_fd(' ', 1);
        i += ft_strlen(vars);
    }
    return (i);
}

int ft_echo_n(char *command)
{
    int i;

    i = -1;
    while (command[++i])
    {
        if (command[i] == ' ')
            i++;
        else
            break ;
    }
    return (i + 2);
}

int ft_arg_echo(char *command, char **vars, int args)
{
	int i;

	i = 0;
    g_bool = 0;
    //ignore_space(&command);
    g_args= args;
    if (args)
    {
        if (vars[1] == NULL)
            return (1);
        else if (vars[1])
        {
            command =ft_cutstr(command, "echo", ft_strlen(command));
            ft_loop_echo(vars, command);
            if (ft_strcmp(vars[1], "-n"))
			    ft_putchar_fd('\n', 1);
        }
        return (1);
    }
    else
        return (0);
    return (-1);
}