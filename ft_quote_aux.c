/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <fjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 19:20:42 by fernando          #+#    #+#             */
/*   Updated: 2020/07/16 15:59:16 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_quote_dollar(char *cmd, int *j)
{
	char *tmp;
	char *aux;

	tmp = ft_cut_end(ft_strrchr(cmd, '$'), Q_DOUBLE, Q_SIMPLE, ' ');
    aux = ft_echo_var(tmp);
    ft_putstr_fd(aux, 1);
	*j += ft_strlen(tmp) + 1;//aux == 0 ? ft_strlen(tmp) : ft_strlen(tmp) + 1;
	if (cmd[*j] == ' ')
		ft_putchar_fd(' ', 1);
	free(tmp);
}

static void ft_quote_aux(char *cmd, int *j)
{
	if (cmd[*j] == '\\')
	{
        if (cmd[*j + 1] == Q_DOUBLE || cmd[*j + 1] == Q_SIMPLE)
		{
			*j += 1;
            ft_putchar_fd(cmd[*j], 1);
		}
	}
	if (cmd[*j + 1] == '\0')
    {
			ft_putchar_fd(cmd[*j], 1);
			g_bool = 1;
			return ;
			*j += 1;
    }
	if (cmd[*j] != Q_DOUBLE && cmd[*j] != Q_SIMPLE)
			ft_putchar_fd(cmd[*j], 1);
}

int	ft_quote_snd(char *cmd, int *i)
{
	int j;

	j = -1;
	while (cmd[++j])
	{
		if ((cmd[j] == Q_DOUBLE || cmd[j] == Q_SIMPLE) &&
            (cmd[j + 1] == '\0'|| cmd[j + 1] == ' ' ||
            cmd[j + 1] == '$'))
			{
                if (cmd[j + 1] == '$')
                {
					ft_quote_dollar(cmd, &j);
					if (cmd[j] == Q_DOUBLE || cmd[j] == Q_SIMPLE)
						continue ;
                }
				if (cmd[j + 1] == ' ')
					ft_putchar_fd(' ', 1);
				j++;
				break ;
			}
		if (cmd[j - 1] != Q_DOUBLE && cmd[j - 1] != Q_SIMPLE &&
			cmd[j] == ' ' && cmd[j + 1] != ' ' && cmd[j + 1] != '\0')
				*i += 1;
		ft_quote_aux(cmd, &j);
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
        if (command[i] == ' ') //|| command[i] == '\t')
			i++;
        if (command[i] == '$')
		{
			tmp = ft_cut_end(command, Q_DOUBLE, Q_SIMPLE, '\0');
    		aux = ft_echo_var(tmp);
    		ft_putstr_fd(aux, 1);
    		i += ft_strlen(ft_strrchr(tmp, '$')) - 1;
			free(tmp);
		}
       	else if (command[i] == Q_DOUBLE || command[i] == Q_SIMPLE)
           	break ;
        else if (command[i] != ' ')
            ft_putchar_fd(command[i], 1);
    }
	return (i);
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