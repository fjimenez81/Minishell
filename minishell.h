/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <fjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/18 21:05:01 by fernando          #+#    #+#             */
/*   Updated: 2020/06/30 18:05:54 by fjimenez         ###   ########.fr       */
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
# define Q_DOUBLE '\"'
# define Q_SIMPLE '\''
# define TOK_LIMITS " \t\n\r\a"

char    **g_envp;
int     g_bool;

int	    ft_strcmp(const char *s1, const char *s2);
char	*ft_strnew(size_t size);
int     ft_len_tab(char **args);
void	*ft_memalloc(size_t size);

int     ft_search_c(char *s, int c);
void    ft_free_tab(char **str);
int 	ft_isspace(int c);
void	ignore_space(char **line);
void    ft_swap(char **a, char **b);
int		ft_isalpha(int c);
int     ft_first_chr(char **s, char c);
char    *ft_cutstr(char *src, char *cut, size_t len);
char    *ft_cut_end(char *s, int a, int b, int c);



char	**ft_str_tok(char *s, char *sep);
char    *ft_strstr(char *str, char *to_find);

int     ft_arg_echo(char *command, char **vars, int args);
int     ft_arg_cd(char **args, int command);
int     ft_arg_env(char **args, int command);
int		ft_arg_export(char **vars, int args);
int		ft_arg_unset(char **vars, int args);

void	init_env(char **env);

char    *ft_echo_var(char *tmp);

void	ft_loop_echo(char **vars, char *command);
int 	ft_not_quote(char *vars, char *command);
int 	ft_echo_n(char *command);
int		ft_quote_fst(char *command);
int		ft_quote_snd(char *cmd, int *i);


char	**ft_split_cmd(char const *s, char c);

#endif