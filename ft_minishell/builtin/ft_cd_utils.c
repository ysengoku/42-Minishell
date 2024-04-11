/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 08:26:03 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/11 14:11:10 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	t_env	*to_find;

	to_find = find_env_var(base, destination);
	if (to_find == NULL)
	{
		ft_fprintf(2, "minishell: cd: %s not set\n", destination);
		return (NULL);
	}
	path = ft_strdup(to_find->value);
	if (!path)
	{
		ft_perror("malloc", 1);
		return (NULL);
	}
	return (path);
}

char	*concatenate_path(t_base *base, char *curpath)
{
	t_env	*pwd;
	char	*concatenated_path;

	pwd = find_env_var(base, "PWD");
	if (pwd == NULL)
	{
		ft_free((void *)curpath, 1);
		return (NULL);
	}
	concatenated_path = ft_calloc(ft_strlen(pwd->value)
			+ ft_strlen(base->lst->arg[1]) + 2, sizeof(char));
	if (!concatenated_path)
	{
		ft_perror("malloc", 1);
		ft_free((void *)curpath, 1);
		return (NULL);
	}
	ft_strcpy(concatenated_path, pwd->value);
	if (concatenated_path[ft_strlen(concatenated_path) - 1] != '/')
		ft_strcat(concatenated_path, "/");
	ft_strcat(concatenated_path, curpath);
	free(curpath);
	return (concatenated_path);
}

static void	ft_canonicalize(int *src, int *dest, char *curpath)
{
	if (curpath[*src] == '/' && curpath[*src + 1] == '.'
		&& (curpath[*src + 2] == '/' || curpath[*src + 2] == '\0'))
		*src += 2;
	else if (curpath[*src] == '/' && curpath[*src + 1] == '.'
		&& curpath[*src + 2] == '.'
		&& (curpath[*src + 3] == '/' || curpath[*src + 3] == '\0'))
	{
		if (*dest > 0)
		{
			while (curpath[--(*dest)] != '/' && *dest > 1)
				;
		}
		*src += 3;
	}
	else
		curpath[(*dest)++] = curpath[(*src)++];
}

void	canonicalize_path(char *curpath)
{
	int	src;
	int	dest;

	src = 0;
	dest = 0;
	while (curpath[src])
		ft_canonicalize(&src, &dest, curpath);
	curpath[dest] = '\0';
	if (!curpath[0])
		ft_strcpy(curpath, "/");
	printf("curpath = %s\n", curpath);
}
