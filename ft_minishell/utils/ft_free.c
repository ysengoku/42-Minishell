/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:55:52 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/21 15:19:42 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_strarr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void free_base(t_base *base)
{
 	t_line *current_node;
	t_line *next_node;
	
    if (base)
	{
		current_node = base->lst;
        while (current_node)
		{
            if (current_node->read)
				ft_free_strarr(current_node->read);
            if (current_node->write)
                ft_free_strarr(current_node->write);
            if (current_node->arg)
				ft_free_strarr(current_node->arg);
            next_node = current_node->next;
            free(current_node);
            current_node = next_node;
        }
        free(base);
    }
}
