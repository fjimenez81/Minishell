/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/28 18:03:57 by fjimenez          #+#    #+#             */
/*   Updated: 2021/02/08 11:35:18 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_isspace(int c)
{
	c = (unsigned char)c;
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' \
		|| c == ' ')
		return (1);
	return (0);
}

void	ft_swap(char **a, char **b)
{
	char *c;

	c = *a;
	*a = *b;
	*b = c;
}

char	*ft_get_var(char *path, int find)
{
	int		i;
	char	*aux;

	i = -1;
	aux = NULL;
	while (g_envp[++i])
	{
		if (!ft_strncmp(g_envp[i], path, ft_strlen(path)))
		{
			aux = ft_strdup(ft_first_ap(g_envp[i], '=') + 1);
			return (aux);
		}
	}
	if (!aux && find == 1)
		ft_putendl_fd("\033[1;31m[Minishell]: cd: HOME not set", 2);
	return (NULL);
}

char	*ft_cutstr(char *src, char *cut)
{
	size_t i;
	size_t j;

	if (!ft_strcmp(cut, ""))
		return (src);
	i = -1;
	j = 0;
	while (src[++i])
	{
		if (src[i] == cut[j] || src[i] == cut[j] - 32)
			j++;
		else
			j = 0;
		if (cut[j] == '\0')
		{
			i++;
			while (ft_isspace(src[i]))
			{
				i += 1;
				j += 1;
			}
			return (src + j);
		}
	}
	return (NULL);
}

char	*ft_cut_end(char *s, int bool)
{
	int		i;
	int		j;
	char	*dest;

	i = -1;
	while (s[++i])
	{
		if ((s[i] == 63 && s[i - 1] == 36) || (s[i] == '{' && s[i - 1] != 92) ||
			((s[i] == 34 || s[i] == 39) && s[i + 1] == '}') || s[i] == '_')
			i++;
		else if ((bool && s[i] == '=') || (!ft_isalnum(s[i]) && i > 0) ||
			(s[i] == '$' && (s[i + 1] == '\0' || s[i + 1] != ' ') && i != 0))
			break ;
	}
	if (s[i] == '}' || (bool == 2 && s[i] == '='))
		i++;
	if (!(dest = (char*)malloc(sizeof(char) * i + 1)))
		return (NULL);
	j = -1;
	i += 1;
	while (s[++j] && --i > 0)
		dest[j] = s[j];
	dest[j] = '\0';
	return (dest);
}
