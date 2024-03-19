/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 08:22:13 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/19 13:57:39 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_base *base)
{
	char	buf[PWD_SIZE];
	int		fd_out;

	(void)base;
	// line = {"pwd", ""} or line = {"pwd", ">", "output"}
	//if (list->write == NULL) 
	fd_out = 1;
	// else
	// fd_out = open(list->write, O_WRONLY);
	if (getcwd(buf, sizeof(buf)) != 0)
	{
		ft_putendl_fd(buf, fd_out);
	}
	else
	{
		// error handling
		//ft_putendl_fd(2, strerror(errno));
	}
	return (0);
}
