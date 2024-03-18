/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:42:01 by dvo               #+#    #+#             */
/*   Updated: 2023/11/17 17:42:03 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;
	t_list	*stock_next;

	tmp = *lst;
	if (*lst != NULL)
	{
		stock_next = tmp->next;
		del(tmp->content);
		free(tmp);
		*lst = NULL;
		tmp = stock_next;
		while (tmp != NULL)
		{
			stock_next = tmp->next;
			del(tmp->content);
			free(tmp);
			tmp = stock_next;
		}
	}
}
