/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 12:20:39 by fjimenez          #+#    #+#             */
/*   Updated: 2019/11/27 12:20:49 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *res;

	if (lst)
	{
		while (*lst)
		{
			res = (*lst)->next;
			ft_lstdelone(*lst, del);
			*(lst) = res;
		}
	}
}
