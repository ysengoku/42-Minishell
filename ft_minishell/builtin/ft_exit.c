/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:28:22 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/25 15:22:37 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* This is a temporary code, should be modified */
int	ft_exit(t_base *base, int exit_status)
{
	unlink_heredoc();
//	rl_clear_history();
	free_base_content(base);
	free_envlist(base);
	free(base);
	exit(exit_status);
	return (0);
}
