/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:28:22 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/05 10:20:21 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_base *base, int exit_status, int fd[2])
{
	ft_close(fd[IN], fd[OUT], 0);
	unlink_heredoc();
	rl_clear_history();
	free_base_content(base);
	free_envlist(base);
	free(base);
	write(1, "exit\n", 5);
	exit(exit_status);
}
