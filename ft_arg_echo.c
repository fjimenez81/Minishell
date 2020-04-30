/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernando <fernando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 15:26:37 by fernando          #+#    #+#             */
/*   Updated: 2020/04/30 21:29:19 by fernando         ###   ########.fr       */
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

static void ft_print_echo(char *str)
{
    int i;

    i = 0;
	while (str[i])
	{
		if (str[i] == Q_DOUBLE || str[i] == Q_SIMPLE)
			i++;
		ft_putchar_fd(str[i++], 1);
	}  
}

static char *ft_echo_var(char *tmp, int len)
{
	int i;
	int j;
	char *aux;

	i = -1;
    aux = ft_strrchr(tmp, '$') + 1;
    while (g_envp[++i])
    {
        j = 0;
        while (++j < len)
        {
            tmp = ft_strstr(g_envp[i], aux);
            if (tmp != NULL)
				tmp = ft_strrchr(tmp, '=') + 1;
            else
                tmp = "";   
        }
    }
    return (tmp);
}

int ft_arg_echo(char *command, char **vars, int args)
{
    //char *tmp;
    char *aux;
    int len;
	int i;
    int bool;
    int j;
    (void)command;

	i = 0;
    bool = 0;
    //ignore_space(&command);
    len = ft_len_tab(vars);
    if (args)
    {
        if (vars[1] == NULL)
            return (1);
        else if (vars[1])//(ft_strcmp(vars[1], "-n") != 0)
        {
            command =ft_cutstr(command, "echo", ft_strlen(command));
            command = ft_strtrim(command, " \t\r\"\'");
            i = 0;
			while (vars[++i])
			{
                if (!ft_strcmp(vars[1], "-n"))
                    i++;
                if (ft_first_chr(&vars[i], Q_DOUBLE) || ft_first_chr(&vars[i], '\''))
                {
                    j = 0;
                    while (command[j])
                    {
                        /*if (ft_first_chr(&command, '$'))
                        {
                            aux = ft_echo_var(vars[i], len);
                            ft_print_echo(aux);
                        }*/
                        if (command[j] == Q_DOUBLE || command[j] == Q_SIMPLE)
                            break ;
                        else
                            ft_putchar_fd(command[j], 1);
                        //command++;
                        j++;
                    }
                    ft_putchar_fd(' ', 1);
                    bool = 1;
                }
                if (ft_first_chr(&vars[i], '$'))
                {
                    aux = ft_echo_var(vars[i], len);
                    ft_print_echo(aux);
                }
                else if (!bool)
                {
                    ft_putstr_fd(vars[i], 1);
				    ft_putchar_fd(' ', 1);
                }
			}
            if (ft_strcmp(vars[1], "-n"))
			    ft_putchar_fd('\n', 1);
            free(command);
            /*command = ft_cutstr(command, "echo", ft_strlen(command));
			tmp = ft_strtrim(command, " \t\a\r");
            if (ft_first_chr(&tmp, '$') || (tmp[0] == '\"' && tmp[1] == '$'))
            {
                tmp = ft_echo_var(tmp, len);
            }
            //ft_print_echo(tmp);
			//free(tmp);*/
        }
        return (1);
    }
    else
    {
        return (0);
    }
    return (-1);
}