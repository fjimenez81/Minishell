/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernando <fernando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/18 21:13:26 by fernando          #+#    #+#             */
/*   Updated: 2020/03/28 21:49:41 by fernando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static char	*read_line(void)
{
	char	*line;

	line = NULL;
	get_next_line(0, &line);
	return (line);
}*/

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
	//int i;
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
		if (!ft_strcmp(line, "\0"))
			free(line);
		command = ft_split(line, ';');
		j = 0;
		while (command[j])
		{		
			vars = ft_str_tok(command[j], " \t\n\r\a\"");
			args = ft_len_tab(vars);
			/*if (ft_search_c(vars[j], '\0'))
			{
				printf("hola");
				free(line);	
			}*/
			if (!ft_strcmp(vars[j], "echo"))
			{
				if (vars[j])
					ft_arg_echo(command[j], vars, args);
				ft_str_free(vars);
			}
	  		else if (!ft_strcmp(vars[j], "cd") || !ft_strcmp(vars[j], "CD"))
			{
				if (vars[j])
				{
					if (!ft_strcmp(vars[j], ".."))
	  					chdir("..");
					else
						ft_arg_cd(vars, args);	
				}	
			}
	  		else if (!ft_strcmp(vars[j], "pwd") || !ft_strcmp(vars[j], "PWD"))
			{
				ft_str_free(vars);
	  			ft_putendl_fd(getcwd(pwd, -1), 1);
			}
			else if (!ft_strcmp(vars[j], "env"))
				ft_arg_env(vars, args);
			else if(!ft_strcmp(vars[j], "exit"))
			{
				system("leaks minishell");
				exit(0);
			}
			else
			{
				ft_putstr_fd("\033[1;31m[Minishell] : ", 1);
				ft_putstr_fd("command not found : ", 1);
				ft_putendl_fd(vars[j], 1);
				ft_str_free(vars);
			}
			j++;
			//free(command[j]);
			//free(vars[j]);
			
			
		}
		ft_str_free(command);
		command = NULL;
		free(vars);
		vars = NULL;
		free(line);
		line = NULL;
   	}
    return (0);
}