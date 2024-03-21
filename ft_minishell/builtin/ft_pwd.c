/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 08:22:13 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/21 11:57:39 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_base *base)
{
	char	buf[PWD_SIZE];
	int		fd_out;

	(void)base;
	//if (list->write == NULL) 
	// fd_out = 1;
	// else
	// fd_out = open(list->write, O_WRONLY);
	check_redirection(base, 0, &fd_out);
	if (getcwd(buf, sizeof(buf)) != 0)
	{
		ft_putendl_fd(buf, fd_out);
		exit(0);
	}
	else
	{
		// error handling
		//exit(1)
	}
}
