/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernando <fernando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 21:08:07 by fernando          #+#    #+#             */
/*   Updated: 2020/04/08 20:48:03 by fernando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_dir(char *path)
{
	struct stat s;

	stat(path, &s);
	if (s.st_mode & S_IFDIR)
		return (1);
	return (0);
}

int ft_arg_cd(char **vars, int args)
{
    char *tmp;

    if (args)
    {
        tmp = ft_strdup(vars[1]);
        if (!is_dir(tmp))
            return (-1);
        chdir(tmp);
        free(tmp);
    }
    
    return(1);
}