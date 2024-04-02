/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 08:26:03 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/02 15:10:31 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*retrive_cwd(t_base *base);

char	*get_pwd(void)
{
	char	*path;
	char	buf[PATH_MAX];

	if (getcwd(buf, sizeof(buf)) == 0)
	{
		ft_perror("getcwd", 1);
		return (NULL);
	}
	path = ft_strdup(buf);
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

char	*get_path_to_parentdir(t_base *base)
{
	char	*path;
	char	*current_dir;
	size_t	end;

	current_dir = retrive_cwd(base);
	end = ft_strlen(current_dir) - 1;
	while (current_dir[end] != '/' && end > 0)
		end --;
	path = ft_calloc(end + 2, sizeof(char));
	if (!path)
	{
		ft_perror("malloc", 1);
		return (NULL);
	}
	ft_strlcpy(path, current_dir, end + 1);
	// opendir -> if error, check upper dir until opendir == ok 
	return (path);
}

static char	*retrive_cwd(t_base *base)
{
	char	buf[PATH_MAX];
	char	*cwd;
	t_env	*pwd_node;
	
	pwd_node = find_env_var(base, "PWD");
	if (pwd_node == NULL)
	{
		cwd = getcwd(buf, sizeof(buf));
		if (!cwd)
		{
			ft_perror("cd", 1);
			return (NULL);
		}
	}
	else
		cwd = pwd_node->value;
	return (cwd);
}
