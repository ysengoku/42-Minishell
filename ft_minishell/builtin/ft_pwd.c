/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 08:22:13 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/19 13:19:08 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_base *base, int fd[2])
{
	char	buf[PATH_MAX];
	t_env	*pwd;

	pwd = find_env_var(base, "PWD");
	if (pwd)
		ft_strcpy(buf, pwd->value);
	else
	{
		if (getcwd(buf, sizeof(buf)) == 0)
		{
			ft_close(fd[IN], fd[OUT], 1);
			return (ft_perror("getcwd", 1));
		}
	}
	ft_putendl_fd(buf, fd[OUT]);
	ft_close(fd[IN], fd[OUT], 0);
	return (0);
}
