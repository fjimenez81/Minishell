/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <fjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/18 21:13:26 by fernando          #+#    #+#             */
/*   Updated: 2020/07/26 19:44:03 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_execute(t_shell *pcs, int i)
{
	char pwd[PATH_MAX];
	
	if (!ft_strcmp(pcs->cmp[0], "cd") || !ft_strcmp(pcs->cmp[0], "~"))
		ft_arg_cd(pcs);
	else if (!ft_strcmp(pcs->cmp[0], "pwd") || !ft_strcmp(pcs->cmp[0], "PWD"))
		ft_putendl_fd(getcwd(pwd, -1), 1);
	else if(!ft_strcmp(pcs->cmp[0], "export"))
		ft_arg_export(pcs, pcs->pipesplit[i]);
	else if(!ft_strcmp(pcs->cmp[0], "unset"))
		ft_arg_unset(pcs->pipesplit[i]);
	else if (!ft_strcmp(pcs->cmp[0], "env"))
		ft_arg_env(pcs);
	else if (!ft_strcmp(pcs->cmp[0], "echo"))
		ft_arg_echo_two(pcs->pipesplit[i], pcs->cmp, pcs->args);
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
	ft_free_tab(pcs->cmp);
}

void ft_redir_fd(t_shell *pcs, int flags, char *dir, int *i)
{
	int		std_out;
	char    *dupout;
	char	*dollar;

	while (ft_isspace(pcs->redir[*i]))
		*i += 1;
	std_out = dup(1);
	if (!ft_strcmp(dir, "<"))
	{
		pcs->in = ft_realloc_str(pcs->redir, ft_len_char(pcs->redir), 2);
		if ((pcs->fd = open(pcs->in, O_RDONLY)) < 0)
		{
			ft_putstr_fd(pcs->in, 1);
			pcs->in = NULL;
			ft_putstr_fd(" : No existe el archivo o directorio\n", 1);
		}
		dollar = ft_cutstr(pcs->redir, "echo", ft_strlen(pcs->redir));
		dupout = ft_realloc_str(dollar, -1, 1);
		ft_putendl_fd(dupout, 1);	
	}
	else
	{
		pcs->out = ft_realloc_str(pcs->redir, ft_len_char(pcs->redir), 2);
		pcs->fd = open(pcs->out, flags, 0644);
		if (!ft_strcmp(pcs->cmp[0], "echo"))
		{
			dollar = ft_cutstr(pcs->redir, "echo", ft_strlen(pcs->redir));
			dupout = ft_realloc_str(dollar, -1, 1);
			dup2(pcs->fd, STDOUT_FILENO);//Pone el standar output en modo escritura
			ft_putendl_fd(dupout, 1);//Y por eso no printa en pantalla y lo escribe en el archivo
		}
	}
	close(pcs->fd);
	dup2(std_out, 1);//Devuelve el standar output a su modo original
}

int ft_check_redir(t_shell *pcs, int j)
{
	int i;
	int quotes;

	i = -1;
	quotes = 0;
	pcs->redir = pcs->pipesplit[j];
	while (pcs->redir[++i])
	{
		if ((pcs->redir[i] == '\"' || pcs->redir[i] == '\"') &&
			pcs->redir[i - 1] != '\\' && quotes == 0)
			quotes = 1;
		else if ((pcs->redir[i] == '\"' || pcs->redir[i] == '\"') &&
			pcs->redir[i - 1] != '\\' && quotes == 1)
			quotes = 0;
		else if (pcs->redir[i] == '>' && quotes == 0)
		{
			pcs->bool_redir = 1;
			i++;
			if (pcs->redir[i] == '>')
			{
				i++;
				ft_redir_fd(pcs, O_RDWR | O_CREAT | O_APPEND, ">>", &i);
			}
			else
				ft_redir_fd(pcs, O_TRUNC | O_RDWR | O_CREAT, ">", &i);
			i += ft_strlen(pcs->redir) - i;
		}
		else if (pcs->redir[i] == '<' && quotes == 0)
		{
			pcs->bool_redir = 1;
			i++;
			ft_redir_fd(pcs, O_RDONLY, "<", &i);
			i += ft_strlen(pcs->redir) - i;
		}
	}
	return (pcs->fd);
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
		pcs->cmp = ft_split(pcs->pipesplit[j], ' ');//cuidado con echo fuciona con ft_split
		pcs->args = ft_len_tab(pcs->cmp);
		pcs->bool_redir = 0;
		pcs->fd = ft_check_redir(pcs, j);
		if (pcs->bool_redir == 0)
			ft_execute(pcs, j);
		else if (pcs->bool_redir == 1)
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