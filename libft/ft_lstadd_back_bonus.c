/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 12:20:06 by fjimenez          #+#    #+#             */
/*   Updated: 2019/11/27 12:20:18 by fjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list *res;

	res = *alst;
	if (alst)
	{
		if (*alst == NULL)
			*alst = new;
		else
		{
			res = ft_lstlast(*(alst));
			res->next = new;
		}
	}
}
