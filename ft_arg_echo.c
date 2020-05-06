/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernando <fernando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 15:26:37 by fernando          #+#    #+#             */
/*   Updated: 2020/05/06 21:34:58 by fernando         ###   ########.fr       */
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

int ft_not_quote(char *vars, char *command)
{
    int i;

    i = 0;
	if (ft_search_c(vars, '$'))
    {
        while (command[i])
        {
            if (command[i] == ' ')
                i++;
            if (command[i] == '$')
                break ;
            else
                ft_putchar_fd(command[i++], 1); 
        }
        ft_putstr_fd(ft_echo_var(vars), 1);
        ft_putchar_fd(' ', 1);
    }
    else
    {
        ft_putstr_fd(vars, 1);
        ft_putchar_fd(' ', 1);
    }
    return (i += ft_search_c(vars, '$') ?
        ft_strlen(vars) + i - 2 : ft_strlen(vars) + 1);
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
    //char *tmp;
    //char *aux;
    //int len;
	int i;
    //int j;


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
			/*while (vars[++i])
			{
                if (!ft_strcmp(vars[i], "-n") && i == 1)
                {
                    i++;                    
                    command += ft_echo_n(command);
                }
				if (!ft_search_c(vars[i], Q_DOUBLE) &&
					!ft_search_c(vars[i], Q_SIMPLE) && !ft_first_chr(&vars[i], '$'))
                        command += ft_not_quote(vars[i], command);
                if (ft_search_c(vars[i], Q_DOUBLE) || ft_search_c(vars[i], Q_SIMPLE))
                {
                    command += ft_quote_fst(command);
                    command += ft_quote_snd(command, &i);
                }
                if (ft_first_chr(&vars[i], '$') && !g_bool)
                {
                    ft_putstr_fd(ft_echo_var(vars[i]), 1);
                    if (vars[i + 1] != NULL)
					    ft_putchar_fd(' ', 1);
                    command += ft_strlen(vars[i]) + 1;
                }
			}*/
            if (ft_strcmp(vars[1], "-n"))
			    ft_putchar_fd('\n', 1);
        }
        return (1);
    }
    else
    {
        return (0);
    }
    return (-1);
}