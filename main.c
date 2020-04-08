/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernando <fernando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/18 21:13:26 by fernando          #+#    #+#             */
/*   Updated: 2020/04/08 21:41:07 by fernando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*char	*read_line(void)
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
		if (ft_search_c(vars[j], '='))
		{
			g_equal = ft_str_tok(vars[j], "=");
			break ;
		}
		if (!ft_strcmp(vars[j], "echo"))
		{
			if (vars[j])
				ft_arg_echo(command[j], vars, args);
		}
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
		{
			ft_strdel(vars);
			return (getcwd(pwd, -1));
		}
		else if (!ft_strcmp(vars[j], "env"))
		{
			ft_arg_env(vars, args);
			ft_strdel(vars);
		}
		else if(!ft_strcmp(vars[j], "exit"))
		{
			system("leaks minishell");
			exit(0);
		}
		else
		{
			ft_putstr_fd("\033[1;31m[Minishell] : ", 1);
			ft_putstr_fd("command not found : ", 1);
			aux = vars[j];
			ft_strdel(vars);
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

static void ft_commands(char **command)
{
	int args;
	int j;
	char *exe;
	char **vars;

	j = 0;
	while (command[j])
	{	
		vars = ft_str_tok(command[j], TOK_LIMITS);
		args = ft_len_tab(vars);
		exe = ft_execute(command, vars, args);
		ft_putendl_fd(exe, 1);
		ft_free_tab(vars);
		j++;	
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
		if (!ft_strcmp(line, "\0"))
			free(line);
		command = ft_split(line, ';');
		ft_commands(command);
		ft_free_tab(command);
		free(line);
   	}
    return (0);
}