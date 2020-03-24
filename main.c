/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernando <fernando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/18 21:13:26 by fernando          #+#    #+#             */
/*   Updated: 2020/03/24 21:34:55 by fernando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void despedida()
{
   	printf("Hasta luego compi!!\n");
   	exit(1);
}*/

/*static char	*read_line(void)
{
	char	*line;

	line = NULL;
	get_next_line(0, &line);
	return (line);
}*/

/*static void	init_env(char ***env, char **envp)
{
	int		i;
	int		j;

	i = -1;
	while (envp[++i])
		NULL;
	(*env) = (char **)malloc(sizeof(char*) * i);
	i = -1;
	while (envp[++i])
	{
		(*env)[i] = (char *)malloc(PATH_MAX + 1);
		j = -1;
		while (envp[i][++j])
			(*env)[i][j] = envp[i][j];
		(*env)[i][j] = 0;
	}
	(*env)[i] = NULL;
	i = -1;
	return ;
}*/

int main(int ac, char **av, char **envp)
{
	int status;
	int command;
	char pwd[PATH_MAX];
	char *line;
	char **args;

    //signal(SIGINT, despedida);
	(void)ac;
	(void)av;
	(void)envp;
	//init_env(&env, envp);
	status = 1;
    while(status)
   	{
		//if (!(getcwd(pwd, -1)))
			//return (1);
		ft_putstr_fd("\033[1;92m[Minishell] ~>\033[0m ", 1);
		if (get_next_line(0, &line) <= 0)
			break ;
		args = ft_split(line, ';');
		command = ft_count_args(args);
		if (!ft_strcmp(args[0], "echo"))
		{
			if (args[1])
				ft_arg_echo(args, command);
			ft_putstr_fd("\n", 1);
		}	
	  	else if (!ft_strcmp(args[0], "cd") || !ft_strcmp(args[0], "CD"))
		{
			if (args[1])
			{
				if (!ft_strcmp(args[1], ".."))
	  				chdir("..");
				else
				{
					ft_arg_cd(args, command);
					//ft_putstr_fd("\n", 1);
				}	
			}
			else
				continue ;	
		}
	  	else if (!ft_strcmp(args[0], "pwd") || !ft_strcmp(args[0], "PWD"))
		{
	  		ft_putstr_fd(getcwd(pwd, -1), 1);
			ft_putstr_fd("\n", 1);
		}
		else
		{
			ft_putstr_fd("\033[1;31m[Minishell] : ", 1);
			ft_putstr_fd("command not found : ", 1);
			ft_putstr_fd(line, 1);
			ft_putstr_fd("\n", 1);
			continue ;
		}
		
	  	//status = 0;
   	}
	system("leaks minishell");
    return (0);
}