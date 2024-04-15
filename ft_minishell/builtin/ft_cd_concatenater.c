/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 08:26:03 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/15 16:05:57 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*concatenate_home(t_base *base, char *curpath);
static char	*concatenate_pwd(t_base *base, char *curpath, int *missing_pwd);
static char	*handle_missingpwd(t_base *base, t_env *pwd, char *path, int *flag);

char	*concatenate_path(t_base *base, char *curpath, int *missing_pwd)
{
	char	*concatenated_path;

	if (ft_strncmp(curpath, "~/", 2) == 0)
		concatenated_path = concatenate_home(base, curpath);
	else
		concatenated_path = concatenate_pwd(base, curpath, missing_pwd);
	free(curpath);
	return (concatenated_path);
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
		base->exit_code = ft_perror("malloc", 1);
		return (NULL);
	}
	ft_strcpy(concatenated_path, home->value);
	if (concatenated_path[ft_strlen(concatenated_path) - 1] != '/')
		ft_strcat(concatenated_path, "/");
	ft_strcat(concatenated_path, curpath + 2);
	return (concatenated_path);
}

static char	*handle_missingpwd(t_base *base, t_env *pwd, char *path, int *flag)
{
	char	*concatenated_path;
	char	*tmp;

	*flag = 1;
	concatenated_path = ft_calloc(ft_strlen(pwd->value)
			+ ft_strlen(base->lst->arg[1]) + 2, sizeof(char));
	if (!concatenated_path)
	{
		base->exit_code = ft_perror("malloc", 1);
		return (NULL);
	}
	ft_strcpy(concatenated_path, pwd->value);
	if (concatenated_path[ft_strlen(concatenated_path) - 1] != '/')
		ft_strcat(concatenated_path, "/");
	ft_strcat(concatenated_path, path);
	tmp = pwd->value;
	pwd->value = ft_strdup(concatenated_path);
	free(tmp);
	if (!pwd->value)
	{
		base->exit_code = ft_perror("malloc", 1);
		return (NULL);
	}
	return (concatenated_path);
}

static char	*concatenate_pwd(t_base *base, char *curpath, int *missing_pwd)
{
	t_env	*pwd;
	char	*cwd;
	char	buf[PATH_MAX];
	char	*concatenated_path;

	cwd = getcwd(buf, sizeof(buf));
	pwd = find_env_var(base, "PWD");
	if (cwd == NULL)
		return (handle_missingpwd(base, pwd, curpath, missing_pwd));
	else
	{
		concatenated_path = ft_calloc(ft_strlen(cwd)
				+ ft_strlen(base->lst->arg[1]) + 2, sizeof(char));
		if (!concatenated_path)
		{
			base->exit_code = ft_perror("malloc", 1);
			return (NULL);
		}
		ft_strcpy(concatenated_path, cwd);
		if (concatenated_path[ft_strlen(concatenated_path) - 1] != '/')
			ft_strcat(concatenated_path, "/");
		ft_strcat(concatenated_path, curpath);
	}
	return (concatenated_path);
}
