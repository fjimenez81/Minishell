/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/22 16:51:37 by fjimenez          #+#    #+#             */
/*   Updated: 2020/10/29 17:31:53 by fjimenez         ###   ########.fr       */
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

void		exit_signal(int sig)
{
	(void)sig;
	ft_putstr_fd("\n\033[1;92m[Minishell] ~>\033[0m ", 1);
	signal(sig, &exit_signal);
}

void		ctrl_d(int fd)
{
	if (fd == 0)
	{
		ft_putstr_fd("exit\n", 1);
		exit(0);
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
}

int			main(int ac, char **av, char **env)
{
	char	*line;
	int		fd;
	t_test	tst;

	signal(SIGINT, &exit_signal);
	signal(SIGQUIT, &exit_signal);
	(void)ac;
	(void)av;
	init_env(env);
	tst.status = 0;
	while (1)
	{
		ft_putstr_fd("\033[1;92m[Minishell] ~>\033[0m ", 1);
		if ((fd = get_next_line(0, &line)) != 0)
		{
			ft_init_struct(&tst, line);
			ft_comands(&tst);
			ft_free_tab(tst.cmd);
			free(line);
		}
		ctrl_d(fd);
	}
	return (0);
}
