/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:12:40 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/03 16:07:36 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_pathname(t_base *base);
static char	**extract_path(t_base *base);

void	execute_command(t_base *base)
{
	char	*pathname;

	if (access(base->lst->arg[0], F_OK) == 0)
	{
		if (access(base->lst->arg[0], X_OK) == -1)
		{
			ft_close_in_child(STDIN_FILENO, STDOUT_FILENO);
			exit(print_error(base->lst->arg[0], "Permission denied", 126));
		}
		pathname = ft_strdup(base->lst->arg[0]);
	}
	else
		pathname = get_pathname(base);
	if (!pathname)
	{
		write(2, "malloc failed\n", 14);
		ft_close_in_child(STDIN_FILENO, STDOUT_FILENO);
		exit(EXIT_FAILURE);
	}
	execve(pathname, base->lst->arg, base->env);
	free(pathname);
	ft_close_in_child(STDIN_FILENO, STDOUT_FILENO);
	exit(ft_perror("execve", 1));
}

static char	*check_pathname(t_base *base, char **path_list, int i)
{
	char	*pathname;

	pathname = ft_calloc(ft_strlen(path_list[i])
			+ ft_strlen(base->lst->arg[0]) + 2, sizeof(char));
	if (!pathname)
	{
		ft_free_strarr(path_list);
		ft_close_in_child(STDIN_FILENO, STDOUT_FILENO);
		exit(ft_perror("malloc", 1));
	}
	ft_strcpy(pathname, path_list[i]);
	if (pathname[ft_strlen(path_list[i]) - 1] != '/')
		ft_strcat(pathname, "/");
	ft_strcat(pathname, base->lst->arg[0]);
	if (access(pathname, F_OK) == 0)
	{
		if ((access(pathname, X_OK) == 0))
			return (pathname);
		base->exit_code = 126;
	}
	free(pathname);
	return (NULL);
}

static char	*get_pathname(t_base *base)
{
	int		i;
	char	**path_list;
	char	*pathname;

	i = 0;
	base->exit_code = 127;
	path_list = extract_path(base);
	while (path_list[i])
	{
		pathname = check_pathname(base, path_list, i);
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
		exit(print_error(base->lst->arg[0], "command not found", 127));
	else
		exit(print_error(base->lst->arg[0], "Permission denied", 126));
}

static char	**extract_path(t_base *base)
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
				exit(ft_perror("malloc", 1));
			break ;
		}
		current_node = current_node->next;
	}
	if (!tmp)
		exit(print_error(base->lst->arg[0], "command not found", 127));
	path_list = ft_split(tmp, ':');
	free(tmp);
	if (!path_list)
		exit(ft_perror("malloc", 1));
	return (path_list);
}
