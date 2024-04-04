/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 08:53:04 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/04 10:57:50 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_chdir(char *curpath, t_base *base);
static char	*concatenate_path(t_base *base, char *curpath);
static void	canonicalize_path(char *curpath);
static int	retry_cwd(t_base *base);

int	ft_cd(t_base *base)
{
	char	*curpath;

	if (base->lst->arg[1] == NULL || ft_strncmp(base->lst->arg[1], ".", 2) == 0
		|| ft_strncmp(base->lst->arg[1], "~", 2) == 0
		|| ft_strncmp(base->lst->arg[1], "~/", 3) == 0)
		curpath = get_path(base, "HOME");
	else if (ft_strncmp(base->lst->arg[1], "-", 2) == 0)
		curpath = get_path(base, "OLDPWD");
	else
		curpath = ft_strdup(base->lst->arg[1]);
	if (!curpath)
		return (1);
	if (curpath[0] != '/')
		curpath = concatenate_path(base, curpath);
	if (!curpath)
		return (1);
	canonicalize_path(curpath);
	if (!curpath)
		return (ft_free((void *)curpath, 0));
	if (ft_chdir(curpath, base) == 1)
		return (ft_free((void *)curpath, 1));
	if (base->lst->arg[1] && ft_strncmp(base->lst->arg[1], "-", 2) == 0)
		printf("%s\n", curpath);
	return (ft_free((void *)curpath, 0));
}

static int	ft_chdir(char *curpath, t_base *base)
{
	t_env	*pwd;
	t_env	*oldpwd;
	char	*tmp;

	pwd = find_env_var(base, "PWD");
	oldpwd = find_env_var(base, "OLDPWD");
	if (pwd == NULL || oldpwd == NULL)
		return (1);
	if (chdir(curpath) == -1)
	{
		if (ft_strcmp(base->lst->arg[1], "./") == 0)	
			return (retry_cwd(base));
		ft_fprintf(2, "minishell: cd: %s: %s\n", base->lst->arg[1],
			strerror(errno));
		return (1);
	}
	tmp = oldpwd->value;
	oldpwd->value = pwd->value;
	free(tmp);
	pwd->value = ft_strdup(curpath);
	if (!pwd->value)
		return (ft_perror("malloc", 1));
	return (0);
}

static char	*concatenate_path(t_base *base, char *curpath)
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

static void	canonicalize_path(char *curpath)
{
	int	src;
	int	dest;

	src = 0;
	dest = 0;
	while (curpath[src])
	{
		if (curpath[src] == '/' && curpath[src + 1] == '.'
			&& (curpath[src + 2] == '/' || curpath[src + 2] == '\0'))
			src += 2;
		else if (curpath[src] == '/' && curpath[src + 1] == '.'
			&& curpath[src + 2] == '.'
			&& (curpath[src + 3] == '/' || curpath[src + 3] == '\0'))
		{
			if (dest > 0)
			{
				while (dest > 0 && curpath[--dest] != '/')
					;
			}
			src += 3;
		}
		else
			curpath[dest++] = curpath[src++];
	}
	curpath[dest] = '\0';
}

static int	retry_cwd(t_base *base)
{
	char	buf[PATH_MAX];
	char	*tmp;
	t_env	*pwd;

	pwd = find_env_var(base, "PWD");
	if (getcwd(buf, sizeof(buf)) == NULL)
	{
		if (pwd)
		{
			tmp = pwd->value;
			pwd->value = ft_calloc(ft_strlen(pwd->value) + 4, sizeof(char));
			if (!pwd->value)
				pwd->value = tmp;
			else
			{
				ft_strcpy(pwd->value, tmp);
				if (pwd->value[ft_strlen(pwd->value) - 1] != '/')
					ft_strcat(pwd->value, "/");
				ft_strcat(pwd->value, base->lst->arg[1]);
				free(tmp);
			}	
		}
		return (print_error("cd", DELETED_CWD, 1));
	}
	return (chdir(buf));
}
