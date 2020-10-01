/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <fjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/18 21:05:01 by fernando          #+#    #+#             */
/*   Updated: 2020/10/01 17:09:31 by fjimenez         ###   ########.fr       */
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
# define TOK_LIMITS " \t"
# define SIDEIN 1
# define SIDEOUT 0
# define STDOUT 1
# define STDIN 0


typedef struct  s_test
{
    int     status;
    int     cut;
    int     d_qu;
    int     s_qu;
    int     i;
    int     key;
    int     bool;
    int     bool2;
    int     len_env;
    char    *aux;
    char    *error;
    char    *dollar;
    char    *c_keys;
    char    *paths[3];
    char    **cmd;
    char    **var_exp;
    char    **c_export;
    int     ck_key;
    int     check_fdot;
    int     check_fdin;
    int     fdot_j;
    int     fdin_k;
    int     pass;
    int     fd_tst;
    pid_t   *pid;
}               t_test;

typedef struct s_shell
{
    char        **pipesplit;
    char        **setfd;
    char        **env;
    char        **aux_exp;
    char        *cmd;
    char        *dollar;
    char        *out;
    char        *in;
    char        *redir;
    char        *paths[3];
    int         args;
    int         quotes;
    int         equal;
    int         check_fd;
    int         bool_redir;
    char        **cmp;
    int         enter;
    int         ret;
    int         std_out;
    int         std_in;
    int         status;
    int         pipes[2];
    pid_t       pid;
    int         n_pipe;
    int			*fd_in;
	int			*fd_out;
	int			flag_in;
	int			flag_out;
    char        *test;
    struct s_shell        *previus;
}               t_shell;

char     **g_envp;

int	    ft_strcmp(const char *s1, const char *s2);
char	*ft_strnew(size_t size);
int     ft_len_tab(char **args);
void	*ft_memalloc(size_t size);
void    ft_free_tab(char **str);
int 	ft_isspace(int c);
void	ignore_space(char **line);
void    ft_swap(char **a, char **b);
int		ft_isalpha_cm(int c);
char    *ft_cutstr(char *src, char *cut);
char    *ft_cut_end(char *s);
char    *ft_realloc_str(t_test *tmp, char *str, int i, int cut);
void    ft_realloc_aux_two(char *str, t_test *test);
char    *ft_realloc_var(char *str, char *res, t_test *tmp);
char    *ft_join_char(char *s, int c);
int     ft_len_char(char *str);
char    *ft_pass_space(t_shell *pcs, char *str);
void    ft_sort_export();
char    *ft_check_dollar(t_test *tst, t_shell *pcs, int j, int bool);
char	**ft_str_tok(char *s, char *sep);
char    *ft_strstr(char *str, char *to_find);
int     ft_arg_cd(t_shell *pcs, t_test *tst);
int     ft_arg_env(t_shell *pcs, t_test *tst);
int		ft_arg_export(t_test *tst, t_shell *pcs, int j);
void    ft_check_var_loop(t_test *tst);
int		ft_arg_unset(char *vars);
int     ft_arg_echo(t_shell *pcs, t_test *tst, int i);
char    *ft_print_var(char *aux);
void	init_env(char **env);
int     ft_check_redir(t_test *tst, t_shell *pcs, int j, int pass);
char	**ft_split_cmd(char const *s, char c);
void    ft_check_pipes(t_shell *pcs, t_test *tst, int j);
void    ft_loop_pipes(char **aux, t_test *tst);
int     ft_arg_exe(t_shell *pcs, t_test *tst, int i);

char    *ft_dollar_aux_one(t_test *tst, char *tmp, char *res);

#endif