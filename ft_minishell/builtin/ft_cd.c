/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 08:53:04 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/26 15:17:37 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*get_path(t_base *base, char *destination);
static char		*get_path_to_parentdir(void);
static int		ft_chdir(char *path, t_base *base);
static t_env	*find_oldpwd(t_base *base);

int	ft_cd(t_base *base)
{
	char	*path;

	if (base->lst->arg[1] == NULL || ft_strncmp(base->lst->arg[1], ".", 2) == 0
		|| ft_strncmp(base->lst->arg[1], "~", 2) == 0
		|| ft_strncmp(base->lst->arg[1], "~/", 3) == 0)
		path = get_path(base, "HOME");
	else if (ft_strncmp(base->lst->arg[1], "/", 2) == 0)
		path = ft_strdup("/");
	else if (ft_strncmp(base->lst->arg[1], "-", 2) == 0)
		path = get_path(base, "OLDPWD");
	else if (ft_strncmp(base->lst->arg[1], "..", 3) == 0)
		path = get_path_to_parentdir();
	else
		path = ft_strdup(base->lst->arg[1]);
	if (!path)
		return (EXIT_FAILURE);
	if (ft_chdir(path, base) == 1)
	{
		free(path);
		return (EXIT_FAILURE);
	}
	free(path);
	return (0);
}

static char	*get_path(t_base *base, char *destination)
{
	char	*path;
	t_env	*current_node;

	current_node = base->envn;
	while (current_node)
	{
		if (ft_strcmp(current_node->key, destination) == 0)
		{
			path = ft_strdup(current_node->value);
			if (!path)
			{
				ft_perror("malloc", 1);
				return (NULL);
			}
			return (path);
		}
		current_node = current_node->next;
	}
	print_error("cd", "No such file or directory", 1);
	return (NULL);
}

static char	*get_path_to_parentdir(void)
{
	char	*path;
	char	current_path[PWD_SIZE];
	size_t	end;

	if (getcwd(current_path, sizeof(current_path)) == 0)
	{
		ft_perror("getcwd", 1);
		return (NULL);
	}
	end = ft_strlen(current_path) - 1;
	while (current_path[end] != '/' && end > 0)
		end --;
	path = ft_calloc(end + 2, sizeof(char));
	if (!path)
	{
		ft_perror("malloc", 1);
		return (NULL);
	}
	ft_strlcpy(path, current_path, end + 1);
	return (path);
}

static int	ft_chdir(char *path, t_base *base)
{
	char	next_oldpwd[PWD_SIZE];
	t_env	*oldpwd;
	char	*tmp;

	oldpwd = find_oldpwd(base);
	if (oldpwd == NULL)
		return (print_error(CD, "OLDPWD not found", 1));
	if (getcwd(next_oldpwd, sizeof(next_oldpwd)) == 0)
		return (ft_perror("getcwd", EXIT_FAILURE));
	if (chdir(path) == -1)
	{
		ft_fprintf(2, "minishell: cd: %s: %s\n", base->lst->arg[1],
			strerror(errno));
		return (EXIT_FAILURE);
	}
	tmp = oldpwd->value;
	oldpwd->value = ft_strdup(next_oldpwd);
	if (!oldpwd->value)
		return (ft_perror("malloc", EXIT_FAILURE));
	free(tmp);
	return (0);
}

static t_env	*find_oldpwd(t_base *base)
{
	t_env	*oldpwd;

	oldpwd = base->envn;
	while (oldpwd)
	{
		if (ft_strcmp(oldpwd->key, "OLDPWD") == 0)
			break ;
		oldpwd = oldpwd->next;
	}
	return (oldpwd);
}
