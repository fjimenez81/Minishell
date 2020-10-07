/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 07:42:29 by fjimenez          #+#    #+#             */
/*   Updated: 2020/10/07 19:10:10 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _GET_NEXT_LINE_H
# define _GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

int		get_next_line(const int fd, char **line);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s1, int c);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	ft_strdel(char **str);

#endif
