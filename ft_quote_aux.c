/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernando <fernando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 19:20:42 by fernando          #+#    #+#             */
/*   Updated: 2020/05/05 21:20:00 by fernando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	ft_quote_snd(char *vars, char *command, int *i, int *cont)
{
	while (*command)
	{
		if ((*command == Q_DOUBLE || *command == Q_SIMPLE) &&
            (*(command + 1) == '\0'|| *(command + 1) == ' ' ||
            *(command + 1) == '$'))
			{
                if (*(command + 1) == '$')
                {
                    aux = ft_echo_var(vars[i], len);
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
		if (*(command - 1) != Q_DOUBLE && *(command - 1) != Q_SIMPLE &&
			*command == ' ' && *(command + 1) != ' ' && (i + 1) < g_args)
				*i += 1;
		if (*command != Q_DOUBLE && *command != Q_SIMPLE)
			ft_putchar_fd(*command, 1);
		command++;
	}
}*/

static void ft_aux_fst(char *vars, int *size)
{
	char *tmp;
	char *aux;

	tmp = ft_cut_end(vars, Q_DOUBLE, Q_SIMPLE);
    aux = ft_echo_var(tmp);
    ft_putstr_fd(aux, 1);
    *size += ft_strlen(aux) + 1;
	free(tmp);
}

void ft_quote_fst(char *vars, char *command, int *cont)
{
	int i;
	int size;
	
	i = -1;
	size = 0;
    while (command[++i])
    { 
        if (command[i] == ' ' || command[i] == '\t')
		{
			i++;
            *cont += 1;
		}
        if (command[i] == '$')
        {
			ft_aux_fst(vars, &size);
			i += size - 1;
			*cont += size;
        }
       	else if (command[i] == Q_DOUBLE || command[i] == Q_SIMPLE)
           	break ;
        else
		{
            ft_putchar_fd(command[i], 1);
			*cont += 1;
		}
    }
}