/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 11:35:17 by fjimenez          #+#    #+#             */
/*   Updated: 2021/01/30 19:06:09 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_line_eof(char *line)
{
	int		byte;

	byte = 0;
	while ((g_minish->fd_line = read(0, &byte, 1)) != -1)
	{
		ft_putstr_fd("  \b\b", 1);
		signal(SIGINT, &ft_ctrl);
		if ((g_minish->exit2 == 3 && g_minish->fd_line == 0) ||
			byte == '\n' || byte == '\0' || byte < 2)
			break ;
		else if (g_minish->fd_line > 0)
		{
			g_minish->count++;
			if (g_minish->exit2 == 3)
				g_minish->count2++;
			g_minish->line_aux = byte == '\t' ? ft_join_char(line, ' ') :
				ft_join_char(line, byte);
			free(line);
			line = g_minish->line_aux;
		}
	}
	return (line);
}

int		ft_check_sintax(t_test *t, char *line)
{
	t->i = -1;
	t->d_qu = 0;
	t->s_qu = 0;
	t->aux = ft_strtrim(line, " \t");
	while (t->aux[++t->i])
	{
		ft_aux_loop_quotes(t->aux, t);
		if (!ft_print_syntax(t))
		{
			g_status = 258;
			return (0);
		}
		if ((t->aux[t->i] == 92 || t->aux[t->i] == '|') &&
			t->aux[t->i + 1] == 0 && !t->d_qu && !t->s_qu)
		{
			ft_print_error("ADMIN: ", NULL, "Multilines are not allowed");
			free(t->aux);
			return (0);
		}
	}
	free(t->aux);
	return (1);
}

void	ft_build_pipes(t_shell *p)
{
	int	i;
	int	len;
	int **pipearray;

	i = 0;
	len = 0;
	p->pids = 0;
	while (p->pipesplit[len])
		len++;
	if (len == 0)
		return ;
	pipearray = ft_calloc(len, sizeof(int *));
	if (pipearray == NULL)
		exit(1);
	while (i + 1 < len)
	{
		pipearray[i] = ft_calloc(3, sizeof(int));
		if (pipearray[i] == NULL)
			exit(1);
		if (pipe(pipearray[i]) == -1)
			exit(1);
		i++;
	}
	p->pipes = pipearray;
}

void	ft_comands(t_test *tst, char *line)
{
	int		i;
	t_shell	pcs;

	if (!ft_check_sintax(tst, line))
	{
		free(line);
		return ;
	}
	ft_bzero(&pcs, sizeof(t_shell));
	tst->cmd = ft_split_cmd(line, ';');
	i = -1;
	while (tst->cmd[++i])
	{
		pcs.pipesplit = ft_split_cmd(tst->cmd[i], '|');
		pcs.ret = EXIT_SUCCESS;
		pcs.n_pipe = ft_len_tab(pcs.pipesplit);
		ft_loop_pipes(&pcs);
		ft_free_tab(pcs.pipesplit);
	}
	ft_free_tab(tst->cmd);
	free(line);
}

void	ft_loop_pipes(t_shell *pcs)
{
	int		n;

	n = 0;
	ft_build_pipes(pcs);
	ft_pipelize(n, pcs);
	ft_wait_pcs(pcs);
}
