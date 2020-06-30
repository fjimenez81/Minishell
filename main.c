/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <fjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/18 21:13:26 by fernando          #+#    #+#             */
/*   Updated: 2020/06/30 16:13:38 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_execute(char **command, char ** vars)
{
	char pwd[PATH_MAX];
	int args;

	args = ft_len_tab(vars);
	ignore_space(command);
	if (!ft_strcmp(vars[0], "echo"))
		ft_arg_echo(command[0], vars, args);	
	else if (!ft_strcmp(vars[0], "cd") || !ft_strcmp(vars[0], "~"))
	{
		if (!ft_strcmp(vars[0], ".."))
			chdir("..");
		else
			ft_arg_cd(vars, args);
	}
	else if (!ft_strcmp(vars[0], "pwd") || !ft_strcmp(vars[0], "PWD"))
		ft_putendl_fd(getcwd(pwd, -1), 1);
	else if (!ft_strcmp(vars[0], "env"))
		ft_arg_env(vars, args);
	else if(!ft_strcmp(vars[0], "export"))
		ft_arg_export(vars, args);
	else if(!ft_strcmp(vars[0], "unset"))
		ft_arg_unset(vars, args);
	else if(!ft_strcmp(vars[0], "exit"))
	{
		system("leaks minishell");
		exit(0);
	}
	else
	{
		ft_putstr_fd("\033[1;31m[Minishell] : ", 1);
		ft_putstr_fd("command not found : ", 1);
		ft_putendl_fd(vars[0], 1);
	}
}

static void ft_commands(char **command)
{
	int i;
	char **vars;
	
	i = -1;
	while (command[++i])
	{
		vars = ft_str_tok(command[i], TOK_LIMITS);
		ft_execute(command, vars);
		ft_free_tab(vars);	
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
		//if (!ft_strcmp(line, "\0"))
			//free(line);
		command = ft_split_cmd(line, ';');
		ft_commands(command);
		ft_free_tab(command);
		free(line);
   	}
    return (0);
}