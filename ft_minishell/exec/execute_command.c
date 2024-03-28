/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:12:40 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/26 16:19:09 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_pathname(t_base *base);
static char	**extract_path(t_base *base);
static void	perror_exit(char *message, int exit_status);

void	execute_command(t_base *base)
{
	char	*pathname;

	if (access(base->lst->arg[0], X_OK) == 0)
		pathname = ft_strdup(base->lst->arg[0]);
	else
		pathname = get_pathname(base);
	if (!pathname)
	{
		write(2, "malloc failed\n", 14);
		ft_close_in_child(STDIN_FILENO, STDOUT_FILENO);
		exit(EXIT_FAILURE);
	}
	execve(pathname, base->lst->arg, base->env);
	ft_perror("execve", 1);
	free(pathname);
	ft_close_in_child(STDIN_FILENO, STDOUT_FILENO);
	exit(EXIT_FAILURE);
}

static char	*get_pathname(t_base *base)
{
	int		i;
	char	**path_list;
	char	*pathname;

	i = 0;
	path_list = extract_path(base);
	while (path_list[i])
	{
		pathname = ft_calloc(ft_strlen(path_list[i])
				+ ft_strlen(base->lst->arg[0]) + 2, sizeof(char));
		if (!pathname)
			return (ft_free_strarr(path_list), NULL);
		ft_strcpy(pathname, path_list[i]);
		if (pathname[ft_strlen(path_list[i]) - 1] != '/')
			ft_strcat(pathname, "/");
		ft_strcat(pathname, base->lst->arg[0]);
		if (access(pathname, X_OK) == 0)
			return (ft_free_strarr(path_list), pathname);
		free(pathname);
		i++;
	}
	print_error(base->lst->arg[0], "command not found", 1);
	ft_free_strarr(path_list);
	ft_close_in_child(STDIN_FILENO, STDOUT_FILENO);
	exit(EXIT_FAILURE);
}

static char	**extract_path(t_base *base)
{
	int		i;
	char	*tmp;
	char	**path_list;

	i = -1;
	tmp = NULL;
	while (base->env[++i])
	{
		if (ft_strncmp(base->env[i], "PATH=", 5) == 0)
		{
			tmp = ft_substr(base->env[i], 5, ft_strlen(base->env[i]) - 5);
			if (!tmp)
				perror_exit("malloc", EXIT_FAILURE);
			break ;
		}
	}
	path_list = ft_split(tmp, ':');
	free(tmp);
	if (!path_list)
		perror_exit("malloc", EXIT_FAILURE);
	return (path_list);
}

static void	perror_exit(char *message, int exit_status)
{
	write(2, "minishell: ", 11);
	perror(message);
	exit(exit_status);
}
