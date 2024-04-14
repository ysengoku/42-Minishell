/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:39:05 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/11 15:41:45 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*concatenate_home(t_base *base, char *curpath);
static char	*concatenate_pwd(t_base *base, char *curpath);
static void	ft_canonicalize(int *src, int *dest, char *curpath);

char	*concatenate_path(t_base *base, char *curpath)
{
	char	*concatenated_path;

	if (ft_strncmp(curpath, "~/", 2) == 0)
		concatenated_path = concatenate_home(base, curpath);
	else
		concatenated_path = concatenate_pwd(base, curpath);
	free(curpath);
	return (concatenated_path);
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
}

static char	*concatenate_home(t_base *base, char *curpath)
{
	t_env	*home;
	char	*concatenated_path;

	home = find_env_var(base, "HOME");
	if (home == NULL)
		return (NULL);
	concatenated_path = ft_calloc(ft_strlen(home->value)
			+ ft_strlen(base->lst->arg[1]) + 2, sizeof(char));
	if (!concatenated_path)
	{
		ft_perror("malloc", 1);
		return (NULL);
	}
	ft_strcpy(concatenated_path, home->value);
	if (concatenated_path[ft_strlen(concatenated_path) - 1] != '/')
		ft_strcat(concatenated_path, "/");
	ft_strcat(concatenated_path, curpath + 2);
	return (concatenated_path);
}

static char	*concatenate_pwd(t_base *base, char *curpath)
{
	t_env	*pwd;
	char	*concatenated_path;

	pwd = find_env_var(base, "PWD");
	if (pwd == NULL)
		return (NULL);
	concatenated_path = ft_calloc(ft_strlen(pwd->value)
			+ ft_strlen(base->lst->arg[1]) + 2, sizeof(char));
	if (!concatenated_path)
	{
		ft_perror("malloc", 1);
		return (NULL);
	}
	ft_strcpy(concatenated_path, pwd->value);
	if (concatenated_path[ft_strlen(concatenated_path) - 1] != '/')
		ft_strcat(concatenated_path, "/");
	ft_strcat(concatenated_path, curpath);
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
	else if (curpath[*src] == '/' && curpath[*src + 1] == '/')
		*src += 1;
	else
		curpath[(*dest)++] = curpath[(*src)++];
}
