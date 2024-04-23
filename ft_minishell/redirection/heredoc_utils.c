/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:03:01 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/23 17:01:40 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_heredoc(void)
{
	// write(1, "> ", 2);
	g_received_signal = 0;
}

void	unlink_heredoc(void)
{
	if (access(HEREDOC, F_OK) != -1)
		unlink(HEREDOC);
}