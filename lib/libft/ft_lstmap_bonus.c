/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:42:25 by dvo               #+#    #+#             */
/*   Updated: 2023/11/17 17:42:26 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_wrtlst(t_list *ini, t_list *a, void (*del)(void *))
{
	t_list	*tmp;

	tmp = malloc(sizeof(t_list));
	if (tmp == NULL)
	{
		a->next = NULL;
		ft_lstclear(&ini, del);
		return (NULL);
	}
	return (tmp);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*a;
	t_list	*ini;
	t_list	*tmp;

	if (lst == 0 || f == 0)
		return (0);
	a = malloc(sizeof(t_list));
	if (a == NULL)
		return (NULL);
	a->content = f(lst->content);
	ini = a;
	lst = lst->next;
	while (lst != NULL)
	{
		tmp = ft_wrtlst(ini, a, del);
		if (tmp == NULL)
			return (NULL);
		a->next = tmp;
		tmp->content = f(lst->content);
		lst = lst->next;
		a = tmp;
	}
	a->next = NULL;
	return (ini);
}
