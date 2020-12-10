/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/22 16:51:37 by fjimenez          #+#    #+#             */
/*   Updated: 2020/12/10 21:10:00 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_comands(t_test *tst)
{
	int		i;
	char	**aux;

	i = -1;
	while (tst->cmd[++i])
	{
		aux = ft_split_cmd(tst->cmd[i], '|');
		ft_loop_pipes(aux, tst);
	}
}

void		ft_ctrl(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\b\b  \n\033[1;92m[Minishell] ~>\033[0m ", 1);
		g_quit = 1;
	}
	else if (sig == SIGQUIT)
		ft_putstr_fd("\b\b  \b\b", 1);
	
}

void		ctrl_d(int fd, t_test *tst)
{
	if (fd == 0)
	{
		ft_putendl_fd("exit", 1);
		if (g_quit && tst->exit != 127)
			exit(1);
		else if (tst->exit == 130 && WEXITSTATUS(tst->status) != 127)
			exit(130);	
		else
			exit(WEXITSTATUS(tst->status));	
	}	
}

void		ft_init_struct(t_test *tst, char *line)
{
	tst->len_env = ft_len_tab(g_envp);
	tst->paths[0] = "/bin/";
	tst->paths[1] = "/usr/bin/";
	tst->paths[2] = "";
	tst->cmd = ft_split_cmd(line, ';');
	tst->error = "\033[1;31m[Minishell] : command not found : ";
	g_minish = tst;
}

int			main(int ac, char **av, char **env)
{
	char	*line;
	int		fd;
	//int		byte;
	//char	*aux;
	t_test	tst;

	(void)ac;
	(void)av;
	init_env(env);
	tst.status = 0;
	while (1)
	{
		signal(SIGINT, &ft_ctrl);
		signal(SIGQUIT, &ft_ctrl);
		ft_putstr_fd("\033[1;92m[Minishell] ~>\033[0m ", 1);
		// sh.string = ft_strdup("");
		// b = 0;
		// while ((rd = read(0, &b, 1)) != -1)
		// {
		// 	if (b == '\n' || b == 0)
		// 		break ;
		// 	aux = add_char(b, sh.string);
		// 	free(sh.string);
		// 	sh.string = aux;
		// }
		// line = ft_strdup("");
		// fd = 0;
		// while ((fd = read(0, &byte, 1)) != -1)
		// {
		// 	if (byte == '\n' || byte == 0 || g_run)
		// 		break ;
		// 	aux = ft_join_char(line, byte);
		// 	free(line);
		// 	line = aux;
			
		// }
		// ctrl_d(fd);
		// ft_init_struct(&tst, line);
		// ft_comands(&tst);
		// ft_free_tab(tst.cmd);
		// free(line);
		if ((fd = get_next_line(0, &line)) != 0)
		{
			ft_init_struct(&tst, line);
			ft_comands(&tst);
			ft_free_tab(tst.cmd);
			free(line);
		}
		ctrl_d(fd, &tst);
		if (g_minish->exit == 130 && tst.status == 0)
			g_minish->exit = 0;
		if (tst.cheat == 1)
			tst.cheat = 0;
	}
	return (0);
}
