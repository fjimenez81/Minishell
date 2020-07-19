/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <fjimenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/18 21:13:26 by fernando          #+#    #+#             */
/*   Updated: 2020/07/19 18:33:01 by fjimenez         ###   ########.fr       */
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
	int		k;
	int		j;
	int		size;
	int		prespace;
	int		bfquotes;
	int		aftquotes;
	int		inquotes;
	int		final;
	char	*aux;

	while (ft_isspace(pcs->redir[*i]))
		*i += 1;
	k = -1;
	j = 0;
	size = 0;
	prespace = 1;
	bfquotes = 1;
	aftquotes = 0;
	inquotes = 0;
	final = 0;
	while (pcs->redir[++k])
	{
		if ((pcs->redir[k] == '<' || pcs->redir[k] == '>' ||
			(pcs->redir[k] == ' ' && pcs->redir[k - 1] != '\\')) &&
			(prespace == 1 && bfquotes == 1 && inquotes == 0 && aftquotes == 0))
				j++;
		else if ((pcs->redir[k] == ' ' && pcs->redir[k - 1] == '\\') &&
			((bfquotes == 1 || aftquotes == 1) && inquotes == 0))
			final = 1;
		else if ((pcs->redir[k] != ' ' && pcs->redir[k + 1] == ' ' && pcs->redir[k] != '\\') &&
			((bfquotes == 1 || aftquotes == 1) && inquotes == 0))
		{
			if (final == 1 || aftquotes == 0)
				size++;
			break ;
		}
		else if ((pcs->redir[k] == ' ' && pcs->redir[k - 1] != '\\') &&
			((bfquotes == 1 || aftquotes == 1) && inquotes == 0))
			break ;
		else if (((pcs->redir[k] == '\'' && pcs->redir[k - 1] != '\\') ||
			(pcs->redir[k] == '\"' && pcs->redir[k - 1] != '\\')) &&
			(bfquotes == 1 && inquotes == 0 && aftquotes == 0))
		{
			prespace = 0;
			bfquotes = 0;
			inquotes = 1;
		}
		else if (((pcs->redir[k] == '\'' && pcs->redir[k - 1] != '\\') ||
			(pcs->redir[k] == '\"' && pcs->redir[k - 1] != '\\')) &&
			(bfquotes == 0 && inquotes == 1 && aftquotes == 0))
		{
			size++;
			inquotes = 0;
			aftquotes = 1;
			if (pcs->redir[k + 1] == ' ')
				break ;
		}
		else
		{
			prespace = 0;
			size++;
		}	
	}
	if (!ft_strcmp(dir, "<"))
	{
		aux = ft_pass_quotes(pcs->redir, j, size);
		pcs->in = aux;
		pcs->fd = open(pcs->in, flags, 0644);	
	}
	else
	{
		aux = ft_pass_quotes(pcs->redir, j, size);
		pcs->out = aux;
		pcs->fd = open(pcs->out, flags, 0644);
	}
	close(pcs->fd);
	free(aux);
}

int ft_check_redir(t_shell *pcs, int j)
{
	int i;

	i = -1;
	pcs->redir = pcs->pipesplit[j];
	while (pcs->redir[++i])
	{
		if (pcs->redir[i] == '>')
		{
			i++;
			if (pcs->redir[i] == '>')
			{
				i++;
				ft_redir_fd(pcs, O_RDWR | O_CREAT | O_APPEND, ">>", &i);
			}
			else
				ft_redir_fd(pcs, O_TRUNC | O_RDWR | O_CREAT, ">", &i);
		}
		else if (pcs->redir[i] == '<')
		{
			i++;
			ft_redir_fd(pcs, O_RDONLY, "<", &i);
		}
		i += ft_strlen(pcs->redir) - i;
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
		pcs->fd = ft_check_redir(pcs, j);
		ft_execute(pcs, j);
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