/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <fjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/18 21:13:26 by fernando          #+#    #+#             */
/*   Updated: 2020/07/01 19:32:04 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_execute(t_shell *pcs)
{
	char pwd[PATH_MAX];
	int i;

	i = -1;
	while (pcs->pipesplit && pcs->pipesplit[++i])
	{
		pcs->cmp = ft_str_tok(pcs->pipesplit[i], TOK_LIMITS);
		pcs->args = ft_len_tab(pcs->cmp);
		if (!ft_strcmp(pcs->cmp[0], "echo"))
			ft_arg_echo(pcs->pipesplit[i], pcs->pipesplit, pcs->args);	
		else if (!ft_strcmp(pcs->cmp[0], "cd") || !ft_strcmp(pcs->cmp[0], "~"))
			ft_arg_cd(pcs);
		else if (!ft_strcmp(pcs->cmp[0], "pwd") || !ft_strcmp(pcs->cmp[0], "PWD"))
			ft_putendl_fd(getcwd(pwd, -1), 1);
		else if (!ft_strcmp(pcs->cmp[0], "env"))
			ft_arg_env(pcs);
		else if(!ft_strcmp(pcs->cmp[0], "export"))
			ft_arg_export(pcs);
		else if(!ft_strcmp(pcs->cmp[0], "unset"))
			ft_arg_unset(pcs->pipesplit, pcs->args);
		else if(!ft_strcmp(pcs->cmp[0], "exit"))
		{
			system("leaks minishell");
			exit(0);
		}
		else
		{
			ft_putstr_fd("\033[1;31m[Minishell] : ", 1);
			ft_putstr_fd("command not found : ", 1);
			ft_putendl_fd(pcs->cmp[0], 1);
		}
	}
	ft_free_tab(pcs->cmp);
	

}

static void ft_commands(char **command)
{
	int		i;
	char	**aux;
	char	*tmp;
	t_shell	*pcs;

	if (!(pcs = malloc(sizeof(t_shell) * (ft_len_tab(command) + 1))))
		return ;
	i = -1;
	pcs->cmd = command;
	while (pcs->cmd && pcs->cmd[++i])
	{
		aux = ft_split_cmd(pcs->cmd[i], '|');
		pcs->pipesplit = aux;
		tmp = ft_strtrim(pcs->pipesplit[i], " \t");
		free(pcs->pipesplit[i]);
		pcs->pipesplit[i] = tmp;
		ft_execute(pcs);
	}
	ft_free_tab(aux);
	free(pcs);
	//free(tmp);
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