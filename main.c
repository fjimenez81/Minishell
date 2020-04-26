/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernando <fernando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/18 21:13:26 by fernando          #+#    #+#             */
/*   Updated: 2020/04/26 20:43:40 by fernando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *ft_execute(char **command, char ** vars, int args)
{
	char pwd[PATH_MAX];
	int j;

	j = 0;
	//ignore_space(command);
	while (command[j])
	{
		if (!ft_strcmp(vars[j], "echo"))
			ft_arg_echo(command[j], vars, args);	
		else if (!ft_strcmp(vars[j], "cd") || !ft_strcmp(vars[j], "CD"))
		{
			if (vars[1])
			{
				if (!ft_strcmp(vars[j], ".."))
					chdir("..");
				else
					ft_arg_cd(vars, args);
			}
		}
		else if (!ft_strcmp(vars[j], "pwd") || !ft_strcmp(vars[j], "PWD"))
			ft_putendl_fd(getcwd(pwd, -1), 1);
		else if (!ft_strcmp(vars[j], "env"))
			ft_arg_env(vars, args);
		else if(!ft_strcmp(vars[j], "export"))
			ft_arg_export(vars, args);
		else if(!ft_strcmp(vars[j], "unset"))
			ft_arg_unset(vars, args);
		else if(!ft_strcmp(vars[j], "exit"))
		{
			system("leaks minishell");
			exit(0);
		}
		else
		{
			ft_putstr_fd("\033[1;31m[Minishell] : ", 1);
			ft_putstr_fd("command not found : ", 1);
			return (vars[j]);
		}
		j++;
	}
	return (NULL);
}

static void ft_commands(char **command)
{
	int args;
	int i;
	char *exe;
	char **vars;
	
	i = 0;
	while (command[i])
	{	
		vars = ft_str_tok(command[i], TOK_LIMITS);
		args = ft_len_tab(vars);
		exe = ft_execute(command, vars, args);
		ft_putstr_fd(exe, 1);
		ft_free_tab(vars);
		i++;	
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
		command = ft_split(line, ';');
		ft_commands(command);
		ft_free_tab(command);
		free(line);
   	}
    return (0);
}