/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:28:22 by yusengok          #+#    #+#             */
/*   Updated: 2024/05/02 18:38:59 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_exit(bool is_pipe);

int	ft_exit(t_base *base, t_line *node, int fd[2], bool is_pipe)
{
	int	exit_code;

	print_exit(is_pipe);
	if (node->arg[1])
	{
		if (convert_exitcode(node->arg[1]) != -1
			|| (ft_strcmp(node->arg[1], "-1") == 0))
		{
			exit_code = convert_exitcode(node->arg[1]) % 256;
			if (node->arg[2])
			{
				free_base_content(base);
				return (print_err(EXIT, "too many arguments", NULL, 1));
			}
		}
		else
			exit_code = 2;
	}
	else if (g_received_signal == SIGINT || g_received_signal == SIGQUIT)
		exit_code = 128 + g_received_signal;
	else
		exit_code = base->exit_code;
	ft_close(fd[IN], fd[OUT], 0);
	exit(clear_before_exit(base, exit_code));
	return (0);
}

static void	print_exit(bool is_pipe)
{
	if (is_pipe == false)
		write(2, "exit\n", 5);
}
