/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernando <fernando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 15:26:37 by fernando          #+#    #+#             */
/*   Updated: 2020/05/05 21:23:45 by fernando         ###   ########.fr       */
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

static void ft_not_quote(char *vars, char *command, int *cont)
{
	char *aux;
    int i;

	if (ft_search_c(vars, '$'))
    {
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
        aux = ft_echo_var(vars);
        ft_putstr_fd(aux, 1);
        ft_putchar_fd(' ', 1);
        *cont += ft_strlen(vars) + i - 2;
    }
    else
    {
        ft_putstr_fd(vars, 1);
        ft_putchar_fd(' ', 1);
		*cont += ft_strlen(vars) + 1;
    }
}

static void ft_echo_n(char *command, int *cont)
{
    int i;

    i = -1;
    while (command[++i])
    {
        if (command[i] == ' ')
        {
            i++;
            *cont += 1;
        } 
        else
        {
            *cont += 1;
            break ;
        }
    }
}

int ft_arg_echo(char *command, char **vars, int args)
{
    //char *tmp;
    char *aux;
    //int len;
	int i;
    int bool;
    //int j;
    int cont;

	i = 0;
    bool = 0;
    //ignore_space(&command);
    g_args= args;
    if (args)
    {
        if (vars[1] == NULL)
            return (1);
        else if (vars[1])//(ft_strcmp(vars[1], "-n") != 0)
        {
            command =ft_cutstr(command, "echo", ft_strlen(command));
            i = 0;
            
			while (vars[++i])
			{
                cont = 0;
                if (!ft_strcmp(vars[i], "-n") && i == 1)
                {
                    i++;
                    ft_echo_n(command, &cont);                      
                    command += cont + 2;
                }
				if (!ft_search_c(vars[i], Q_DOUBLE) &&
					!ft_search_c(vars[i], Q_SIMPLE) &&
					!ft_first_chr(&vars[i], '$'))
                    {
						ft_not_quote(vars[i], command, &cont); 
                        command += cont;
                    }  
                if (ft_search_c(vars[i], Q_DOUBLE) || ft_search_c(vars[i], Q_SIMPLE))
                {
                    ft_quote_fst(vars[i], command, &cont);
                    command += cont + 1;
                    //ft_quote_snd(vars[i], command, &i, &cont);
					while (*command)
					{
						if ((*command == Q_DOUBLE || *command == Q_SIMPLE) &&
                            (*(command + 1) == '\0'|| *(command + 1) == ' ' ||
                            *(command + 1) == '$'))
						{
                            if (*(command + 1) == '$')
                            {
                                aux = ft_echo_var(vars[i]);
                                ft_putstr_fd(aux, 1);
                                command += ft_strlen(aux) + 1;
                            }
							if (*(command + 1) == ' ')
								ft_putchar_fd(' ', 1);
                            command++;
							break ;
						}
                        if (*command == '\\')
                        {
                            if (*(command + 1) == Q_DOUBLE || *(command + 1) == Q_SIMPLE)
                            {
                                command++;
                                ft_putchar_fd(*command, 1);
                            }
                        }
						if (*(command + 1) == '\0')
                        {
							ft_putchar_fd(*command, 1);
							bool = 1;
							break ;
                        } 
						if (*(command - 1) != Q_DOUBLE &&
                            *(command - 1) != Q_SIMPLE && *command == ' ' &&
                            *(command + 1) != ' ' && (i + 1) < g_args)
							i++;
						if (*command != Q_DOUBLE && *command != Q_SIMPLE)
							ft_putchar_fd(*command, 1);
						command++;
					}
                }
                if (ft_first_chr(&vars[i], '$') && !bool)
                {
                    
                    aux = ft_echo_var(vars[i]);
                    ft_putstr_fd(aux, 1);
                    if (vars[i + 1] != NULL)
					    ft_putchar_fd(' ', 1);
                    command += ft_strlen(vars[i]) + 1;
                }
                
			}
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