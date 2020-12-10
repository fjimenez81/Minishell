/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 09:53:29 by fjimenez          #+#    #+#             */
/*   Updated: 2020/12/08 19:25:35 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "../minishell.h"

void		ft_strdel(char **str)
{
	if (str != NULL && *str != NULL)
	{
		free(*str);
		*str = NULL;
	}
}

static int	ft_read_line(char **str, char **line, int fd)
{
	int		len;
	char	*tmp;

	len = 0;
	while (str[fd][len] != '\n')
		len++;
	*line = ft_substr(str[fd], 0, len);
	tmp = ft_strdup(&str[fd][len + 1]);
	free(str[fd]);
	str[fd] = tmp;
	return (1);
}

static	int	ft_return(char **str, char **line, int fd, int bytes)
{
	if (bytes < 0)
		return (-1);
	else if (bytes == 0 && (str[fd] == NULL || str[fd][0] == '\0'))
	{
		*line = ft_strdup("");
		ft_strdel(&str[fd]);
		return (0);
	}
	else if (ft_strchr(str[fd], '\n'))
		return (ft_read_line(str, line, fd));
	else
	{
		*line = ft_strdup(str[fd]);
		ft_strdel(&str[fd]);
		return (0);
	}
}

int			get_next_line(int fd, char **line)
{
	char		*buf;
	int			bytes;
	char		*tmp;
	static char *str[4096];

	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0 ||
		(!(buf = (char*)malloc(sizeof(char) * BUFFER_SIZE + 1))))
		return (-1);
	while ((bytes = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[bytes] = '\0';
		if (str[fd] == NULL)
			str[fd] = ft_strdup(buf);
		else
		{
			tmp = ft_strjoin(str[fd], buf);
			free(str[fd]);
			str[fd] = tmp;
		}
		if (ft_strchr(str[fd], '\n'))
			break ;
	}
	free(buf);
	return (ft_return(str, line, fd, bytes));
}
