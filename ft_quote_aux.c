/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernando <fernando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 19:20:42 by fernando          #+#    #+#             */
/*   Updated: 2020/05/06 22:12:09 by fernando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_quote_dollar(char *command, int *j)
{
	char *tmp;
	char *aux;

	tmp = ft_cut_end(ft_strrchr(command, '$'), Q_DOUBLE, Q_SIMPLE, ' ');
    aux = ft_echo_var(tmp);
    ft_putstr_fd(aux, 1);
	*j += ft_strlen(tmp) + 1;//aux == 0 ? ft_strlen(tmp) : ft_strlen(tmp) + 1;
	free(tmp);
}

static void ft_quote_aux(char *command, int *j)
{
	if (command[*j] == '\\')
        if (command[*j + 1] == Q_DOUBLE || command[*j + 1] == Q_SIMPLE)
		{
			*j += 1;
            ft_putchar_fd(command[*j], 1);
		}
	if (command[*j + 1] == '\0')
    {
			ft_putchar_fd(command[*j], 1);
			g_bool = 1;
			*j += 1;
    }
	if (command[*j] != Q_DOUBLE && command[*j] != Q_SIMPLE)
			ft_putchar_fd(command[*j], 1);
}

int	ft_quote_snd(char *command, int *i)
{
	int j;

	j = -1;
	while (command[++j])
	{
		if ((command[j] == Q_DOUBLE || command[j] == Q_SIMPLE) &&
            (command[j + 1] == '\0'|| command[j + 1] == ' ' ||
            command[j + 1] == '$'))
			{
                if (command[j + 1] == '$')
                {
					ft_quote_dollar(command, &j);
					if (command[j] == ' ')
						ft_putchar_fd(' ', 1);
					else if (command[j] == Q_DOUBLE || command[j] == Q_SIMPLE)
						continue ;
                }
				if (command[j + 1] == ' ')
					ft_putchar_fd(' ', 1);
				j++;
				break ;
			}
		ft_quote_aux(command, &j);
		if (command[j - 1] != Q_DOUBLE && command[j - 1] != Q_SIMPLE &&
			command[j] == ' ' && command[j + 1] != ' ' )
				*i += 1;
	}
	return (j);
}

int ft_quote_fst(char *command)
{
	int i;
	char *tmp;
	char *aux;
	
	i = -1;
    while (command[++i])
    { 
        if (command[i] == ' ' || command[i] == '\t')
			i++;
        if (command[i] == '$')
		{
			tmp = ft_cut_end(command, Q_DOUBLE, Q_SIMPLE, '\0');
    		aux = ft_echo_var(tmp);
    		ft_putstr_fd(aux, 1);
    		i += ft_strlen(ft_strrchr(tmp, '$'));
			free(tmp);
		}
       	else if (command[i] == Q_DOUBLE || command[i] == Q_SIMPLE)
           	break ;
        else
            ft_putchar_fd(command[i], 1);
    }
	return (i + 1);
}

void ft_loop_echo(char **vars, char *command)
{
	int i;

	i = 0;
	while (vars[++i])
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
	}
}