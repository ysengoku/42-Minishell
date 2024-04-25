/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:14:23 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/25 10:48:31 by yusengok         ###   ########.fr       */
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

int	is_directory(t_base *base, char *name)
{
	DIR	*dir;

	dir = opendir(name);
	if (dir == NULL)
		return (0);
	if (ft_strchr(name, '/'))
		base->exit_code = print_err(name, "Is a directory", NULL, 126);
	else
		base->exit_code = print_err(name, "command not found", NULL, 126);
	closedir(dir);
	return (1);
}

int	error_in_child(t_base *base, int exit_code, char *s1, char *s2)
{
	if (s1 || s2)
		print_err(s1, s2, NULL, exit_code);
	free_base_content(base);
	free_envlist(base);
	free(base);
	ft_close_in_child(STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO);
	return (exit_code);
}
