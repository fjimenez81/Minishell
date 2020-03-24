/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernando <fernando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 21:08:07 by fernando          #+#    #+#             */
/*   Updated: 2020/03/24 21:33:20 by fernando         ###   ########.fr       */
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

int ft_arg_cd(char **args, int command)
{
    char *tmp;
    if (command)
    {
        tmp = ft_strdup(args[1]);
        if (!is_dir(tmp))
            return (-1);
        chdir(tmp);
    }
    return(1);
}