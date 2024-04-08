/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:14:23 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/08 09:57:19 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_input(int fd_in)
{
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		print_err(strerror(errno), "dup2", NULL, 1);
		exit(EXIT_FAILURE);
	}
	ft_close(fd_in, 0, 0);
}

void	dup_output(int fd_out)
{
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		ft_close(fd_out, 0, 0);
		print_err(strerror(errno), "dup2", NULL, 1);
		exit(EXIT_FAILURE);
	}
	ft_close(fd_out, 0, 0);
}

void	unlink_heredoc(void)
{
	if (access(HEREDOC, F_OK) != -1)
		unlink(HEREDOC);
}
