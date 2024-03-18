/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:41:45 by dvo               #+#    #+#             */
/*   Updated: 2023/11/17 17:41:47 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	tmp = *lst;
	if (*lst == NULL)
	{
		new->next = *lst;
		*lst = new;
	}
	else
	{
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->next = new;
	}
}

/*int	main(void)
{
	t_list * l =  NULL; t_list * l2 =  NULL;
        ft_lstadd_back(&l, ft_lstnew((void*)1));
		ft_lstadd_back(&l, ft_lstnew((void*)2));
		ft_lstadd_back(&l2, ft_lstnew((void*)3));
        ft_lstadd_back(&l2, ft_lstnew((void*)4));
        ft_lstadd_back(&l, l2);
		 free(l);
}*/
