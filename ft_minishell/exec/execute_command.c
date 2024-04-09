/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:12:40 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/08 14:38:42 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_pathname(t_base *base, t_line *node);
static char	**extract_path(t_base *base, t_line *node);
static char	*check_path(t_base *base, t_line *node, char **path_list, int i);

void	execute_command(t_base *base, t_line *node)
{
	char	*pathname;

	if (!node->arg[0][0])
		exit(error_in_child(base, 127, node->arg[0], "command not found"));
	if (node->arg[0][0] == '/')
	{
		if (access(node->arg[0], X_OK) == 0)
		{
			pathname = ft_strdup(node->arg[0]);
			if (!pathname)
				exit(error_in_child(base, 1, strerror(errno), NULL));
		}
		else 
			exit (check_dir(node->arg[0], base));
	}
	else
		pathname = get_pathname(base, node);
	execve(pathname, node->arg, base->env);
	free(pathname);
	if (check_dir(node->arg[0], base) == 126)
		exit(126);
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
	ft_close_in_child(STDIN_FILENO, STDOUT_FILENO);
	if (base->exit_code == 127)
		exit(error_in_child(base, 127, node->arg[0], "command not found"));
	else
		exit(error_in_child(base, 126, node->arg[0], "Permission denied"));
}

static char	**extract_path(t_base *base, t_line *node)
{
	char	*tmp;
	char	**path_list;
	t_env	*current_node;

	tmp = NULL;
	current_node = base->envn;
	while (current_node)
	{
		if (ft_strcmp(current_node->key, "PATH") == 0)
		{
			tmp = ft_strdup(current_node->value);
			if (!tmp)
				exit(error_in_child(base, 1, strerror(errno), NULL));
			break ;
		}
		current_node = current_node->next;
	}
	if (!tmp)
		exit(error_in_child(base, 127, node->arg[0], "command not found"));
	path_list = ft_split(tmp, ':');
	free(tmp);
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
