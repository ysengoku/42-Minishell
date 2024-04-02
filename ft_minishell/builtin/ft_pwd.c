/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 08:22:13 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/02 13:45:19 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_base *base)
{
	char	buf[PWD_SIZE];
	int		fd[2];
	t_env	*pwd;

	fd[IN] = STDIN_FILENO;
	fd[OUT] = STDOUT_FILENO;
	if (check_redirection(base, &fd[IN], &fd[OUT]) == 1)
		return (1);
	pwd = find_env_var(base, "PWD");
	if (pwd == NULL)
	{
		if (getcwd(buf, sizeof(buf)) == 0)
		{
			ft_close(fd[IN], fd[OUT], 1);
			return (ft_perror("getcwd", 1));
		}
		ft_putendl_fd(buf, fd[OUT]);
	}
	else
		ft_putendl_fd(pwd->value, fd[OUT]);
	ft_close(fd[IN], fd[OUT], 0);
	return (0);
}
