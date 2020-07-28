/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <fjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/18 21:05:01 by fernando          #+#    #+#             */
/*   Updated: 2020/07/28 15:29:05 by fjimenez         ###   ########.fr       */
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
# include <fcntl.h>
# include "gnl/get_next_line.h"
# include "libft/libft.h"

# define BUFFER_SIZE 2
# define Q_DOUBLE '\"'
# define Q_SIMPLE '\''
# define TOK_LIMITS " \t"


typedef struct s_shell
{
    char        **pipesplit;
    char        **setfd;
    char        **env;
    char        *cmd;
    char        *out;
    char        *in;
    char        *redir;
    char        *rderror;
    char        *export;
    int         args;
    int         fd;
    int         quotes;
    int         equal;
    int         check_fd;
    int         bool_redir;
    char        **cmp;
    char        *lnarg;
}               t_shell;

char     **g_envp;


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
char    *ft_cut_end(char *s);
char    *ft_realloc_str(char *str, int i, int cut);
char    *ft_join_char(char *s, int c);
int     ft_len_char(char *str);
char    *ft_pass_space(t_shell *pcs, char *str);
void    ft_sort_export();



char	**ft_str_tok(char *s, char *sep);
char    *ft_strstr(char *str, char *to_find);

int     ft_arg_cd(t_shell *pcs);
int     ft_arg_env(t_shell *pcs);
int		ft_arg_export(t_shell *pcs, char *str);
int		ft_arg_unset(char *vars);
int     ft_arg_echo(char *cmd, char **vars, int args);



char    *ft_print_var(char *aux);

void	init_env(char **env);

char    *ft_echo_var(char *tmp);
int     ft_check_redir(t_shell *pcs, int j);

void	ft_loop_echo(char **vars, char *command);
int 	ft_not_quote(char *vars, char *command);
int 	ft_echo_n(char *command);
int		ft_quote_fst(char *command);
int		ft_quote_snd(char *cmd, int *i);


char	**ft_split_cmd(char const *s, char c);

#endif