/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <fjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 13:11:06 by fernando          #+#    #+#             */
/*   Updated: 2020/08/01 19:09:22 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_len_char(char *str)
{
    int i;
    int quotes;

    i = -1;
    quotes = 0;
    while(str[++i])
    {
        if ((str[i] == '\"' || str[i] == '\'') &&
				str[i - 1] != '\\' && quotes == 0)
				quotes = 1;
		else if ((str[i] == '\"' || str[i] == '\'') &&
				str[i - 1] != '\\' && quotes == 1)
				quotes = 0;
        else if ((str[i] == '<' || str[i] == '>') && quotes == 0)
        {
            i++;
            if (str[i] == '>')
                i++;
            while (ft_isspace(str[i]))
                i += 1;
            break ;
        }
    }
    return (i - 1);
}

int             ft_arg_env(t_shell *pcs)
{
	int i;

	if (pcs->args == 1)
	{
        /*if (pcs->env)
	    {ft_putendl_fd("dentro", 1);
		    i = -1;
		    while (pcs->env[++i])
			    if (ft_strcmp(pcs->env[i], "") != 0 && ft_strchr(pcs->env[i], '='))
				    ft_putendl_fd(pcs->env[i], 1);
		    return (1);
	    }*/
       // else
        //{
            i = -1;
		    while (g_envp[++i])
			    if (ft_strcmp(g_envp[i], "") != 0 && ft_strchr(g_envp[i], '='))
				    ft_putendl_fd(g_envp[i], 1);
		    return (1);
        //}
	}
	return (0);
}