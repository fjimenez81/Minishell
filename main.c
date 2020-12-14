/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/22 16:51:37 by fjimenez          #+#    #+#             */
/*   Updated: 2020/12/14 11:31:48 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_ctrl(int sig)
{
	if (sig == SIGINT)
	{
		//if (g_minish->exit2 == -1)
			g_minish->exit2 = 3;
		ft_putstr_fd("\b\b  \n\033[1;92m[Minishell]-1.0$\033[0m ", 1);
		g_quit = 1;
	}
	else if (sig == SIGQUIT)
		ft_putstr_fd("\b\b  \b\b", 1);
}

static void	ctrl_d(t_test *tst)
{
	g_minish->exit2 = -1;
	if (g_minish->fd_line == 0)
	{
		system("leaks minishell");
		ft_putendl_fd("\033[1;31mexit", 1);
		if (g_quit && tst->exit != 127)
			exit(1);
		else if (tst->exit == 130 && WEXITSTATUS(tst->status) != 127)
			exit(130);
		else
			exit(WEXITSTATUS(tst->status));
	}
}

static void	ft_init_struct(t_test *tst)
{
	//tst->len_env = ft_len_tab(g_envp);
	tst->paths[0] = "/bin/";
	tst->paths[1] = "/usr/bin/";
	tst->paths[2] = "";
	g_minish = tst;
	g_minish->count = 0;
	g_minish->count2 = 0;
	g_minish->fd_line = 0;
}

char	*ft_get_line_eof(char *line)
{
	int		byte;
	
	while ((g_minish->fd_line = read(0, &byte, 1)) != -1)
	{
		ft_putstr_fd("  \b\b", 1);
		signal(SIGINT, &ft_ctrl);
		if ((g_minish->exit2 == 3 && g_minish->fd_line == 0) ||
			byte == '\n' || byte == '\0')
			break ;
		else if (g_minish->fd_line > 0)
		{
			g_minish->count++;
			if (g_minish->exit2 == 3)
				g_minish->count2++;
			g_minish->line_aux = ft_join_char(line, byte);
			free(line);
			line = g_minish->line_aux;
		}
	}
	return (line);
}

static void	ft_read_line(t_test *tst)
{
	char	*line;
	char	*aux;

	line = ft_strdup("");
	ft_init_struct(tst);
	line = ft_get_line_eof(line);
	ctrl_d(tst);
	if (g_minish->exit2 == -1 && g_quit == 1)
	{
		aux = g_minish->line_aux;
		free(line);
		g_minish->count3 = g_minish->count - g_minish->count2;
		line = ft_substr(aux, g_minish->count3, ft_strlen(aux));
		g_minish->exit2 = 0;
		g_quit = 0;
	}
	ft_comands(tst, line);
}

int			main(int ac, char **av, char **env)
{
	t_test	tst;

	if (ac != 1)
	{
		ft_putstr_fd("\033[1;31m[Minishell]: ", 1);
		ft_putstr_fd(av[1], 1);
		ft_putendl_fd(": No such file or directory", 1);
		return (127);
	}
	init_env(env);
	tst.status = 0;
	while (1)
	{
		signal(SIGINT, &ft_ctrl);
		signal(SIGQUIT, &ft_ctrl);
		ft_putstr_fd("\033[1;92m[Minishell]-1.0$\033[0m ", 1);
		ft_read_line(&tst);
		if (g_minish->exit == 130 && tst.status == 0)
			g_minish->exit = 0;
		if (tst.cheat == 1)
			tst.cheat = 0;
	}
	return (0);
}
