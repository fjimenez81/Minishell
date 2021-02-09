/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_fds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 08:28:46 by fjimenez          #+#    #+#             */
/*   Updated: 2021/01/31 20:49:45 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_fd(int fd)
{
	if (fd > 1)
		close(fd);
}

void	ft_close_and_dup(t_shell *p, t_dup *redirs)
{
	int i;

	i = 0;
	while (p->pipes[i])
	{
		if (p->pipes[i][0] > 2 && p->pipes[i][0] != redirs->in)
		{
			close(p->pipes[i][0]);
		}
		if (p->pipes[i][1] > 2 && p->pipes[i][1] != redirs->out)
		{
			close(p->pipes[i][1]);
		}
		i++;
	}
	if (redirs->in > 0 && dup2(redirs->in, 0) < 0)
		exit(1);
	if (redirs->out > 0 && dup2(redirs->out, 1) < 0)
		exit(1);
}

void	ft_close_pipes(t_shell *p, int n)
{
	if (p->pipes)
	{
		if (p->pipes[n] && p->pipes[n][1] > 1)
		{
			close(p->pipes[n][1]);
			p->pipes[n][1] = -1;
		}
		if (n > 0 && p->pipes[n - 1] && p->pipes[n - 1][0] > 1)
		{
			close(p->pipes[n - 1][0]);
			p->pipes[n - 1][0] = -1;
		}
	}
}
