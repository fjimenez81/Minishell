/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/22 16:51:37 by fjimenez          #+#    #+#             */
/*   Updated: 2021/02/02 13:41:08 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_ctrl(int sig)
{
	if (sig == SIGINT)
	{
		g_minish->exit2 = 3;
		ft_putstr_fd("\b\b  \n\033[1;92m[Minishell]-1.0$\033[0m ", 1);
		g_quit = 1;
		g_status = 1;
	}
}

void	ctrl_d(void)
{
	g_minish->exit2 = -1;
	if (g_minish->fd_line == 0)
	{
		ft_putendl_fd("\033[1;31mexit", 1);
		exit(g_status);
	}
}

void	ft_init_struct(t_test *tst)
{
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
	tst->line = line;
	ctrl_d();
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

int		main(int ac, char **av, char **env)
{
	t_test	tst;

	if (ac != 1)
	{
		ft_print_error(av[1], NULL, ": No such file or directory");
		return (127);
	}
	init_env(env);
	g_status = 0;
	while (1)
	{
		signal(SIGINT, &ft_ctrl);
		signal(SIGQUIT, &ft_ctrl);
		ft_putstr_fd("\033[1;92m[Minishell]-1.0$\033[0m ", 1);
		ft_rd_line(&tst);
	}
	return (0);
}
