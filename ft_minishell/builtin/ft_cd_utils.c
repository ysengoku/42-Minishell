/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 08:26:03 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/28 08:29:11 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_pwd(void) // Need to review
{
	char	*path;
	char	current_path[PWD_SIZE];

	if (getcwd(current_path, sizeof(current_path)) == 0)
	{
		ft_perror("getcwd", 1);
		return (NULL);
	}
	path = ft_strdup(current_path);
	if (!path)
	{
		ft_perror("malloc", 1);
		return (NULL);
	}
	return (path);
}

char	*get_path(t_base *base, char *destination)
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

t_env	*find_env_var(t_base *base, char *key)
{
	t_env	*pwd;

	pwd = base->envn;
	while (pwd)
	{
		if (ft_strcmp(pwd->key, key) == 0)
			return (pwd);
		pwd = pwd->next;
	}
	print_error(key, " not found", 1);
	return (NULL);
}


char	*get_path_to_parentdir(t_base *base)
{
	char	*path;
	t_env	*pwd;
	size_t	end;

	pwd = find_env_var(base, "PWD");
	if (pwd == NULL)
		return (NULL);

	end = ft_strlen(pwd->value) - 1;
	while (pwd->value[end] != '/' && end > 0)
		end --;
	path = ft_calloc(end + 2, sizeof(char));
	if (!path)
	{
		ft_perror("malloc", 1);
		return (NULL);
	}
	ft_strlcpy(path, pwd->value, end + 1);
	return (path);
}
/*
char	*get_path_to_parentdir(void)
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
*/