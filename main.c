/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernando <fernando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/18 21:13:26 by fernando          #+#    #+#             */
/*   Updated: 2020/03/31 22:02:57 by fernando         ###   ########.fr       */
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

static char *ft_execute(char **command, char **vars, int args)
{
	char *aux;
	char pwd[PATH_MAX];
	int j;
	int i;

	j = 0;
	i = 0;
	while (command[j])
	{
		if (!ft_strcmp(vars[j], "echo"))
		{
			if (vars[j])
				ft_arg_echo(command[j], vars, args);
			ft_str_free(vars);
		}
		else if (!ft_strcmp(vars[j], "cd") || !ft_strcmp(vars[j], "CD"))
		{
			if (vars[1])
			{
				if (!ft_strcmp(vars[j], ".."))
				{
					chdir("..");
					ft_str_free(vars);
					free(command[j]);

					}
					else
						ft_arg_cd(vars, args);	
				}
				ft_str_free(vars);
		}
		else if (!ft_strcmp(vars[j], "pwd") || !ft_strcmp(vars[j], "PWD"))
		{
			ft_str_free(vars);
			ft_str_free(command);
			return (getcwd(pwd, -1));
		}
		else if (!ft_strcmp(vars[j], "env"))
		{
			ft_arg_env(vars, args);
			ft_str_free(vars);
		}
		else if(!ft_strcmp(vars[j], "exit"))
		{
			ft_str_free(vars);
			system("leaks minishell");
			exit(0);
		}
		else
		{
			ft_putstr_fd("\033[1;31m[Minishell] : ", 1);
			ft_putstr_fd("command not found : ", 1);
			aux = vars[j];
			ft_str_free(vars);
			return (aux);
		}
		j++;
	}
	return (NULL);
}

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
	char *line;
	char *tmp;
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
		i = 0;
		while (command[j])
		{	
			vars = ft_str_tok(command[j], TOK_LIMITS);
			args = ft_len_tab(vars);
			tmp = ft_execute(command, vars, args);
			ft_putendl_fd(tmp, 1);
			while (vars[i])
				free(vars[i++]);
			(vars) ? free(vars) : 0;
			j++;
			i = 0;	
		}
		while (command[i])
			free(command[i++]);
		(command) ? free(command) : 0;
		free(line);
   	}
    return (0);
}