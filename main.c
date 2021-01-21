/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/22 16:51:37 by fjimenez          #+#    #+#             */
/*   Updated: 2021/01/11 09:45:59 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_ctrl(int sig)
{
	if (sig == SIGINT)
	{
		g_minish->exit2 = 3;
		ft_putstr_fd("\b\b  \n\033[1;92m[Minishell]-1.0$\033[0m ", 1);
		g_minish->cheat = 1;
		g_quit = 1;
	}
}

void	ctrl_d(t_test *tst)
{
	g_minish->exit2 = -1;
	if (g_minish->fd_line == 0)
	{
		system("leaks minishell");
		ft_putendl_fd("\033[1;31mexit", 1);
		if (g_quit && tst->exit != 127)
			exit(1);
		else if (tst->exit > 129 && WEXITSTATUS(tst->status) != 127)
			exit(tst->exit);
		else
			exit(WEXITSTATUS(tst->status));
	}
}

void	ft_init_struct(t_test *tst)
{
	tst->cheat = 0;
	tst->cd = 0;
	g_minish = tst;
	g_minish->count = 0;
	g_minish->count2 = 0;
	g_minish->fd_line = 0;
}

void	ft_rd_line(t_test *tst)
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
	tst->line = line;
	ft_comands(tst, line);
}

int		main(int ac, char **av, char **env)
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
		ft_rd_line(&tst);
		if (g_minish->exit == 130 && tst.status == 0)
			g_minish->exit = 0;
		if (tst.cheat == 1)
			tst.cheat = 0;
	}
	return (0);
}
