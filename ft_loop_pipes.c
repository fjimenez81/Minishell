/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 11:35:17 by fjimenez          #+#    #+#             */
/*   Updated: 2021/01/22 16:26:25 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*ft_get_line_eof(char *line)
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

int				ft_check_sintax(t_test *t, char *line)
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
			g_minish->exit = 258;
			t->status = 258;
			return (0);
		}
		if ((t->aux[t->i] == 92 || t->aux[t->i] == '|') &&
			t->aux[t->i + 1] == 0 && !t->d_qu && !t->s_qu)
		{
			ft_putstr_fd("\033[1;31m[Minishell]: ", 1);
			ft_putendl_fd("syntax error multilines are not allowed!!", 1);
			free(t->aux);
			return (0);
		}
	}
	free(t->aux);
	return (1);
}

void			ft_comands(t_test *tst, char *line)
{
	int		i;
	char	**aux;
	t_shell	*pcs;

	if (!ft_check_sintax(tst, line))
	{
		free(line);
		return ;
	}
	tst->cmd = ft_split_cmd(line, ';');
	i = -1;
	while (tst->cmd[++i])
	{
		aux = ft_split_cmd(tst->cmd[i], '|');
		if (!(pcs = ft_calloc(ft_len_tab(aux), sizeof(t_shell))))
			return ;
		pcs->ret = EXIT_SUCCESS;
		pcs->n_pipe = ft_len_tab(aux);
		pcs->pipesplit = aux;
		ft_loop_pipes(pcs, tst);
		ft_free_tab(aux);
		free(pcs);
	}
	ft_free_tab(tst->cmd);
	free(line);
}

static void		ft_loop_pipes_aux(t_shell *pcs, t_test *tst, int j)
{
	tst->bool = 0;
	if ((!ft_ck_rd_envp(pcs, tst, "exit") ||
		!ft_strcmp(pcs->cmp[0], "exit")) && (tst->bool = 1))
		ft_arg_exit(tst, pcs, j);
	else if ((!ft_ck_rd_envp(pcs, tst, "cd") ||
			!ft_strcmp(pcs->cmp[0], "cd") ||
			!ft_strcmp(pcs->cmp[0], "~") ||
			!ft_strcmp(pcs->cmp[0], "$HOME") ||
			!ft_strcmp(pcs->cmp[0], "$PWD") ||
			!ft_strcmp(pcs->cmp[0], "$PATH")) && (tst->bool = 1))
		ft_arg_cd(pcs, tst, j);
	else if (!ft_strcmp(pcs->cmp[0], "export") &&
			(tst->bool = 1) && !pcs->bool_redir)
		ft_arg_export(tst, pcs, j);
	else if ((!ft_ck_rd_envp(pcs, tst, "unset") ||
			!ft_strcmp(pcs->cmp[0], "unset")) && (tst->bool = 1))
		ft_arg_unset(pcs, tst, j);
	ft_check_pipes(pcs, tst, j);
}

void			ft_loop_pipes(t_shell *pcs, t_test *tst)
{
	int		j;
	char	*tmp;

	j = -1;
	while (pcs->pipesplit[++j])
	{
		tmp = ft_strtrim(pcs->pipesplit[j], " \t");
		free(pcs->pipesplit[j]);
		pcs->pipesplit[j] = tmp;
		tst->ckqu = ft_realloc_str(tst, pcs->pipesplit[j], -1, 13);
		if (ft_strlen(pcs->pipesplit[j]) == 0 || !tst->ckqu)
		{
			if (!tst->ckqu)
				ft_putendl_fd("multilines are not allowed!!", 1);
			free(tst->ckqu);
			break ;
		}
		pcs->cmp = ft_split(pcs->pipesplit[j], ' ');
		pcs->args = ft_len_tab(pcs->cmp);
		ft_check_redir(tst, pcs, j, 0);
		ft_loop_pipes_aux(pcs, tst, j);
		ft_free_tab(pcs->cmp);
		free(tst->ckqu);
	}
}
