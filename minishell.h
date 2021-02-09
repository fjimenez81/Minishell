/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/18 21:05:01 by fernando          #+#    #+#             */
/*   Updated: 2021/02/08 21:23:08 by fjimenez         ###   ########.fr       */
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
# include "libft/libft.h"

# define BUFFER_SIZE 2
# define TOK_LIMITS " \t"
# define WRITE 1
# define READ 0
# define STDOUT 1
# define STDIN 0

typedef struct	s_dup
{
	int			in;
	int			out;
	char		*input;
	char		*output;
	int			ispipe[2];
	int			bool;
	int			cut;
	int			bool_in;
	int			bool_out;
}				t_dup;

typedef struct	s_test
{
	int			status;
	int			exit;
	int			exit2;
	int			cut;
	int			d_qu;
	int			s_qu;
	int			i;
	int			k;
	int			j;
	int			bool;
	int			bool2;
	char		*aux;
	char		*dollar;
	char		*c_keys;
	char		**cmd;
	char		**var_exp;
	int			check_redir;
	int			ck_key;
	int			count;
	int			count2;
	int			count3;
	char		*line_aux;
	int			fd_line;
	int			one_dollar;
	int			cd;
	char		*line;
	char		*sub;
	int			ret;
	int			slash;
	int			tilde;
	int			cheat;
}				t_test;

typedef struct	s_shell
{
	char		**pipesplit;
	char		**upper;
	int			args;
	int			bool;
	char		**cmp;
	int			ret;
	pid_t		pid;
	int			pids;
	int			**pipes;
	int			is_child;
	int			n;
	int			fd;
	int			n_pipe;
}				t_shell;

char			**g_envp;
int				g_status;
int				g_quit;
t_test			*g_minish;

int				ft_strcmp(const char *s1, const char *s2);
int				ft_len_tab(char **args);
char			*ft_first_ap(const char *s, int c);
void			ft_free_tab(char **str);
int				ft_isspace(int c);
char			**ft_add_str(char **s);
void			ft_swap(char **a, char **b);
char			*ft_cutstr(char *src, char *cut);
char			*ft_cut_end(char *s, int bool);
char			*ft_realloc_str(char *str, int i, int cut);
void			ft_inc_cont(char *s, char *res, t_test *t);
void			ft_realloc_aux_two(char *str, t_test *test);
void			ft_aux_loop_quotes(char *str, t_test *tmp);
char			*ft_realloc_var(char *str, char *res, t_test *tmp);
char			*ft_join_char(char *s, int c);
int				ft_len_char(char *str);
void			ft_sort_export(int fd);
char			*ft_check_dollar(t_test *tst, t_shell *pcs, int j, int bool);
char			*ft_strstr(char *str, char *to_find);
int				ft_arg_cd(t_shell *pcs);
char			*ft_get_var(char *path, int find);
int				ft_arg_env(t_shell *pcs);
int				ft_arg_export(t_shell *pcs);
void			ft_check_var_loop(t_shell *pcs, t_test *tst, int i);
int				ft_arg_unset(t_shell *pcs);
int				ft_arg_echo(t_shell *pcs);
char			*ft_print_var(char *s);
void			init_env(char **env);
void			ft_free_all(t_test *t, t_shell *pcs);
void			ft_wordlen_aux(char **s, int *count);
void			ft_getcount_aux(char **s);
char			**ft_split_cmd(char *s, char c);
void			ft_check_pipes(t_shell *pcs, t_test *tst, int j);
void			ft_loop_pipes(t_shell *pcs);
char			*ft_get_line_eof(char *line);
void			ft_rd_line(t_test *tst);
void			ft_ctrl(int sig);
void			ctrl_d();
void			ft_init_struct(t_test *tst);
void			ft_comands(t_test *tst, char *line);
void			ft_arg_exe(t_shell *pcs);
void			ft_multiple_redir(t_shell *pcs, t_test *tst);
void			ft_get_redir(t_shell *pcs, t_test *tst);
void			ft_file_out(t_shell *pcs, t_test *tst, int flags);
char			*ft_dollar_aux_one(t_test *tst, char *tmp, char *res);
void			ft_arg_exit(t_shell *pcs);
int				ft_arg_pwd(t_shell *pcs);
void			ft_print_error(char *error, char *path, char *s);
void			ft_err_exit(t_shell *pcs);
void			ft_ctrl_process(int sig);
int				ft_ck_rd_envp(t_shell *pcs, char *str);
int				ft_print_syntax(t_test *tst);
int				ft_pt_syntax_aux_three(t_test *t);
void			ft_only_path(t_shell *pcs);
int				ft_redir_in_aux(char *s, t_dup *redirs, t_test *tst);
int				ft_redir_out_aux(char *s, t_dup *redirs, t_test *tst);
int				ft_check_n(char *s);
char			*ft_quit_n(char *s);
int				ft_execute(t_shell *pcs, int i, t_test *tst);
int				ft_check_redir(t_dup *redirs, char *s);
void			ft_free_int_tab(int **arr);
void			ft_build_pipes(t_shell *p);
void			ft_wait_pcs(t_shell *p);
int				ft_pipelize(int n, t_shell *p);
void			ft_check_fork(t_shell *p, t_dup *redirs);
void			ft_close_fd(int fd);
void			ft_close_and_dup(t_shell *p, t_dup *redirs);
void			ft_close_pipes(t_shell *p, int n);
void			ft_change_case(char **args);
int				ft_isupper(char *s);
void			ft_lst_cmd(char *s);
void			ft_change_dollar(t_shell *p, t_dup *redirs, int n);
char			*ft_tilde_redir(t_test *t, char *res);
int				ft_cut_redir_out(t_test *t, t_dup *redirs, char *s);
int				ft_redir_check_out(t_dup *redirs, char *s, t_test *t);
int				ft_cut_redit_in(t_test *t, t_dup *redirs, char *s);
int				ft_open_redir_in(t_dup *redirs, char *s, t_test *t);

#endif
