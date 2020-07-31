/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <fjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/18 21:13:26 by fernando          #+#    #+#             */
/*   Updated: 2020/07/31 20:59:03 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_arg_exe(t_shell *pcs, int i)
{
	char	*join;
	int		exe;
	int		j;
	(void)i;

	pcs->paths[0] = ft_strdup("/bin/");
	pcs->paths[1] = ft_strdup("/usr/bin/");
	pcs->paths[2] = ft_strdup("");
	exe = -1;
	j = 0;
	while (exe == -1 && j < 3)
	{
		join = ft_strjoin(pcs->paths[j], pcs->cmp[0]);
		j++;
		free(join);
		exe = execve(join, pcs->cmp, NULL);
		if (j == 3 && exe == -1)
		{
			ft_putstr_fd("\033[1;31m[Minishell] : ", 1);
			ft_putstr_fd("command not found : ", 1);
			ft_putendl_fd(pcs->cmp[0], 1);
		}
		if (j == 3 && exe == -1)
			exit(127);
	}
	return (0);
}

static int	ft_execute(t_shell *pcs, int i)
{
	char pwd[PATH_MAX];
	int ret;
	int exe;
	
	pcs->fd = ft_check_redir(pcs, i);
	ret = 0;
	exe = 0;
	if ((!ft_strcmp(pcs->cmp[0], "pwd") || !ft_strcmp(pcs->cmp[0], "PWD")) && pcs->enter == 1 && (exe = 1))
	{
		ft_putendl_fd(getcwd(pwd, -1), 1);
		ret = 1;
	}
	else if(!ft_strcmp(pcs->cmp[0], "export") && pcs->enter == 1 && (exe = 1))
		ret = ft_arg_export(pcs, pcs->pipesplit[i]);
	else if(!ft_strcmp(pcs->cmp[0], "unset") && pcs->enter == 1 && (exe = 1))
		ret = ft_arg_unset(pcs->pipesplit[i]);
	else if (!ft_strcmp(pcs->cmp[0], "env") && pcs->enter == 1 && (exe = 1))
		ret = ft_arg_env(pcs);
	else if (!ft_strcmp(pcs->cmp[0], "echo") && pcs->bool_redir == 0 && pcs->enter == 1 && (exe = 1))
		ret = ft_arg_echo(pcs, i);
	else if (exe == 0)
		ret = ft_arg_exe(pcs, i);
	return (ret);
}

static void ft_loop_pipes(char **aux)
{
	int		j;
	char	*tmp;
	t_shell	*pcs;

	if (!(pcs = malloc(sizeof(t_shell) * (ft_len_tab(aux) + 1))))
			return ;
	j = -1;
	while (++j < ft_len_tab(aux))
	{
		pcs->pipesplit = aux;
		tmp = ft_strtrim(pcs->pipesplit[j], " \t");
		free(pcs->pipesplit[j]);
		pcs->pipesplit[j] = tmp;
		pcs->cmp = ft_split_cmd(pcs->pipesplit[j], ' ');
		pcs->args = ft_len_tab(pcs->cmp);
		pcs->enter = 1;
		if(!ft_strcmp(pcs->cmp[0], "exit"))//no funciona con pipes al cerrar deja abierto los procesos
		{
			pcs->enter = 0;
			system("leaks minishell");
			exit(0);
		}
		else if (!ft_strcmp(pcs->cmp[0], "cd") || !ft_strcmp(pcs->cmp[0], "~"))//no fuciona en pipes por eso lo pongo por delante
		{
			pcs->enter = 0;
			pcs->ret = ft_arg_cd(pcs);
		}
		pcs->bool_redir = 0;
		pcs->std_in = dup(0);
		pcs->std_out = dup(1);
		if (ft_len_tab(pcs->pipesplit) > 1)
			pipe(pcs->pipes);
		pcs->pid = fork();
		if (pcs->pid == 0)
		{
			dup2(pcs->pipes[1], 1);
			if (j > 0)
				dup2(pcs->pipes[0], 0);
			if (j == ft_len_tab(pcs->pipesplit) - 1)
				dup2(pcs->std_out, 1);
			pcs->ret = ft_execute(pcs, j);
			exit(pcs->ret);
		}
		else
		{
			waitpid(pcs->pid, &pcs->status, 0);
			if (ft_len_tab(pcs->pipesplit) > 1)
			{
				close(pcs->pipes[1]);
				if (j == ft_len_tab(pcs->pipesplit))
					close(pcs->pipes[0]);
				if (j > 0)//&& j == ft_len_tab(pcs->pipesplit) - 1)	
					close(pcs->pipes[0]);
				if (WIFEXITED(pcs->status))
					pcs->ret = WEXITSTATUS(pcs->status);
			}
		}
		ft_free_tab(pcs->cmp);
	}
	ft_free_tab(aux);
	free(pcs);
}

static void ft_commands(char **command)
{
	int		i;
	char	**aux;

	i = -1;
	while (command[++i])
	{
		aux = ft_split_cmd(command[i], '|');
		ft_loop_pipes(aux);
	}
}

int main(int ac, char **av, char **env)
{
	char *line;
	char **command;

    //signal(SIGINT, despedida);
	(void)ac;
	(void)av;
	init_env(env);
    while(1)
   	{
		ft_putstr_fd("\033[1;92m[Minishell] ~>\033[0m ", 1);
		if (get_next_line(0, &line) <= 0)
			break ;
		command = ft_split_cmd(line, ';');
		ft_commands(command);
		ft_free_tab(command);
		free(line);
   	}
    return (0);
}