/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:37:04 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/20 16:31:44 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_pathname(t_base *base);
static char	**extract_path(t_base *base);

void	ft_execve(t_base *base)
{
	char	*pathname;
	char	*tmp;

/*--- get path ---*/
	if (access(base->lst->arg[0], X_OK) == 0)
		pathname = ft_strdup(base->lst->arg[0]);
	else
		pathname = get_pathname(base);
	tmp = base->lst->arg[0];
	base->lst->arg[0] = pathname;
	free(tmp);
/*--- execute ---*/
	execve(pathname, base->lst->arg, base->env);
	ft_write(strerror(errno), "execve");
	// free all here
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
			return (ft_free_arr(path_list), NULL);
		ft_strcpy(pathname, path_list[i]);
		if (pathname[ft_strlen(path_list[i]) - 1] != '/')
			ft_strcat(pathname, "/");
		ft_strcat(pathname, base->lst->arg[0]);
		if (access(pathname, X_OK) == 0)
			return (ft_free_arr(path_list), pathname);
		free(pathname);
		i++;
	}
	ft_free_arr(path_list);
	return ("invalidcommand"); //// To change
}

static char	**extract_path(t_base *base)
{
	int		i;
	char	*tmp;
	char	**path_list;

	i = 0;
	tmp = NULL;
	while (base->env[i])
	{
		if (ft_strncmp(base->env[i], "PATH=", 5) == 0)
		{
			tmp = ft_substr(base->env[i], 5, ft_strlen(base->env[i]) - 5);
			// if (!tmp)
			// 	ft_freearr_and_exit(base->lst->arg, EXIT_FAILURE, "Error: ", "malloc failed");
			break ;
		}
		i++;
	}
	path_list = ft_split(tmp, ':');
	free(tmp);
	// if (!path_list)
	// 	ft_freearr_and_exit(base->lst->arg, EXIT_FAILURE, "Error: ", "malloc failed");
	return (path_list);
}
