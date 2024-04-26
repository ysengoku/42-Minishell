/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:03:01 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/26 13:34:05 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_heredoc(void)
{
	write(1, "> ", 2);
	g_received_signal = 0;
}

void	unlink_heredoc(t_base *base)
{
	t_line	*current;

	current = base->lst;
	while (current)
	{
		if (current->heredoc[0])
		{
			if (access(current->heredoc, F_OK) != -1)
				unlink(current->heredoc);
		}
		current = current->next;
	}
}

int	free_heredoc(char *line, int fd, int status)
{
	close(fd);
	ft_free(line, 0);
	return (status);
}
