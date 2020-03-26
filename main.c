/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernando <fernando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/18 21:13:26 by fernando          #+#    #+#             */
/*   Updated: 2020/03/26 20:19:33 by fernando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_env(char **env)
{
	int		i;

	i = 0;
	while (env[i])
		i++;
	if (!(g_envp = (char **)malloc(sizeof(char*) * (i + 1))))
		return ;
	g_envp[i] = NULL;
	i = -1;
	while (env[++i])
		g_envp[i] = ft_strdup(env[i]);
	return ;
}

int main(int ac, char **av, char **env)
{
	int args;
	int j;
	int i;
	char **vars;
	char pwd[PATH_MAX];
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
		command = ft_split(line, ';');
		j = 0;
		while (command[j])
		{
			vars = ft_str_tok(command[j], " \t\n\r\a\"");
			args = ft_len_tab(vars);
			if (!ft_strcmp(vars[0], "echo"))
			{
				if (vars[1])
					ft_arg_echo(command[j], vars, args);
				//ft_str_free(&line);
			}	
	  		else if (!ft_strcmp(vars[0], "cd") || !ft_strcmp(vars[0], "CD"))
			{
				if (vars[1])
				{
					if (!ft_strcmp(vars[1], ".."))
	  					chdir("..");
					else
						ft_arg_cd(vars, args);	
				}	
			}
	  		else if (!ft_strcmp(vars[0], "pwd") || !ft_strcmp(vars[0], "PWD"))
			{
	  			ft_putendl_fd(getcwd(pwd, -1), 1);
				ft_str_free(vars);
			}
			else if (!ft_strcmp(vars[0], "env"))
				ft_arg_env(vars, args);
			else if(!ft_strcmp(vars[0], "exit"))
			{
				//printf("Es es un leak : %p\n", 0x7f83d8c02f40);
				system("leaks minishell");
				exit(1);
			}
			else
			{
				ft_putstr_fd("\033[1;31m[Minishell] : ", 1);
				ft_putstr_fd("command not found : ", 1);
				ft_putendl_fd(line, 1);
			}
			j += 1;
		}
		i = 0;
		while (command[i])
			free(command[i++]);
		free(line);
		//ft_str_free(vars);
   	}
	system("leaks minishell");
    return (0);
}