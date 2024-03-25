/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 08:22:13 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/25 14:55:17 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_base *base)
{
	char	buf[PWD_SIZE];
	int		fd_out;

	(void)base;
	// Need to check all files (in/out) in order
	// If there is an open error, stop & return (1)
	if (check_redirection(base, 0, &fd_out) == 1)
		return (EXIT_FAILURE);
	if (getcwd(buf, sizeof(buf)) == 0)
	{
		//error handling 
		return (EXIT_FAILURE);
	}
	ft_putendl_fd(buf, fd_out);
	return (0);
}
