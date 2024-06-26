/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:12:40 by yusengok          #+#    #+#             */
/*   Updated: 2024/05/02 23:23:57 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_pathname(t_base *base, t_line *node);
static char	**extract_path(t_base *base, t_line *node);
static char	*check_path(t_base *base, t_line *node, char **path_list, int i);

void	execute_command(t_base *base, t_line *node)
{
	char	*pathname;

	pathname = NULL;
	if (!node->arg[0][0] || !ft_strcmp(node->arg[0], "..")
		|| !ft_strcmp(node->arg[0], "."))
		exit(error_in_child(base, 127, node->arg[0], "command not found"));
	if (is_directory(base, node->arg[0]) == 1)
		exit(error_in_child(base, base->exit_code, NULL, NULL));
	if (ft_strchr(node->arg[0], '/') || access(node->arg[0], X_OK) == 0)
	{
		pathname = ft_strdup(node->arg[0]);
		if (!pathname)
			exit(error_in_child(base, 1, strerror(errno), NULL));
		execve(pathname, node->arg, base->env);
		free(pathname);
		if (errno == EACCES)
			exit(error_in_child(base, 126, node->arg[0], strerror(errno)));
		if (errno == ENOTDIR)
			exit(error_in_child(base, 127, node->arg[0], strerror(errno)));
		exit(error_in_child(base, 127, node->arg[0], strerror(errno)));
	}
	pathname = get_pathname(base, node);
	execve(pathname, node->arg, base->env);
	free(pathname);
	exit(error_in_child(base, 1, node->arg[0], strerror(errno)));
}

static char	*get_pathname(t_base *base, t_line *node)
{
	int		i;
	char	**path_list;
	char	*pathname;

	i = 0;
	base->exit_code = 127;
	path_list = extract_path(base, node);
	while (path_list[i])
	{
		pathname = check_path(base, node, path_list, i);
		if (pathname != NULL)
		{
			ft_free_strarr(path_list);
			return (pathname);
		}
		i++;
	}
	ft_free_strarr(path_list);
	if (base->exit_code == 127)
		exit(error_in_child(base, 127, node->arg[0], "Command not found"));
	else
		exit(error_in_child(base, 126, node->arg[0], "Permission denied"));
}

static char	**extract_path(t_base *base, t_line *node)
{
	char	*tmp;
	char	**path_list;
	t_env	*path;

	tmp = NULL;
	path = find_env_var(base, "PATH");
	if (path == NULL)
		exit(error_in_child(base, 127, node->arg[0],
				"No such file or directory"));
	tmp = path->value;
	path_list = ft_split(tmp, ':');
	if (!path_list)
		exit(error_in_child(base, 1, strerror(errno), NULL));
	return (path_list);
}

static char	*check_path(t_base *base, t_line *node, char **path_list, int i)
{
	char	*pathname;

	pathname = ft_calloc(ft_strlen(path_list[i])
			+ ft_strlen(node->arg[0]) + 2, sizeof(char));
	if (!pathname)
	{
		ft_free_strarr(path_list);
		exit(error_in_child(base, 1, strerror(errno), NULL));
	}
	ft_strcpy(pathname, path_list[i]);
	if (pathname[ft_strlen(path_list[i]) - 1] != '/')
		ft_strcat(pathname, "/");
	ft_strcat(pathname, node->arg[0]);
	if (access(pathname, F_OK) == 0)
	{
		if ((access(pathname, X_OK) == 0))
			return (pathname);
		base->exit_code = 126;
	}
	free(pathname);
	return (NULL);
}
