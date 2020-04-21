/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernando <fernando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/18 21:05:01 by fernando          #+#    #+#             */
/*   Updated: 2020/04/21 19:55:06 by fernando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include <limits.h>
# include <dirent.h>
# include "gnl/get_next_line.h"
# include "libft/libft.h"

# define BUFFER_SIZE 2
# define TOK_LIMITS " \n\r\a\""

char    **g_envp;
char    **g_var;
int		g_bool;

int	    ft_strcmp(const char *s1, const char *s2);
char	*ft_strnew(size_t size);
int     ft_len_tab(char **args);
void	*ft_memalloc(size_t size);

int     ft_search_c(char *s, int c);
void    ft_free_tab(char **str);
int 	ft_isspace(int c);
void	ignore_space(char **line);



char	**ft_str_tok(char *s, char *sep);

int     ft_arg_echo(char *command, char **vars, int args);
int     ft_arg_cd(char **args, int command);
int     ft_arg_env(char **args, int command);
int		ft_arg_export(char **vars, int args);
int		ft_arg_unset(char **vars, int args);

void	init_env(char **env);

#endif