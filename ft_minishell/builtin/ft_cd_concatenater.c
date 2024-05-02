/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_concatenater.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 08:26:03 by yusengok          #+#    #+#             */
/*   Updated: 2024/05/02 23:25:27 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_dot_or_dotdot(char *path);
static char	*handle_missingpwd(t_base *base, t_env *pwd, char *path, int *flag);
static int	update_pwd_in_missingpwd(t_base *base, t_env *pwd, char *path);
static char	*set_concatenated_path(t_base *base, char *curpath, char *cwd);

char	*concatenate_path(t_base *base, char *curpath, int *missing_pwd)
{
	t_env	*pwd;
	char	*cwd;
	char	buf[PATH_MAX];
	char	*concatenated;

	cwd = getcwd(buf, sizeof(buf));
	pwd = find_env_var(base, "PWD");
	if (cwd == NULL && is_dot_or_dotdot(curpath) == 1)
	{
		concatenated = handle_missingpwd(base, pwd, curpath, missing_pwd);
		if (!concatenated)
		{
			free(curpath);
			return (NULL);
		}
	}
	else
	{
		concatenated = set_concatenated_path(base, curpath, cwd);
		if (!concatenated)
			return (NULL);
	}
	free(curpath);
	return (concatenated);
}

static char	*set_concatenated_path(t_base *base, char *curpath, char *cwd)
{
	char	*concatenated;

	concatenated = ft_calloc(ft_strlen(cwd)
			+ ft_strlen(curpath) + 2, sizeof(char));
	if (!concatenated)
	{
		base->exit_code = print_err_malloc();
		free(curpath);
		return (NULL);
	}
	ft_strcpy(concatenated, cwd);
	if (concatenated[ft_strlen(concatenated) - 1] != '/')
		ft_strcat(concatenated, "/");
	ft_strcat(concatenated, curpath);
	return (concatenated);
}

static int	is_dot_or_dotdot(char *path)
{
	int	i;

	i = 0;
	if (path[i] != '.')
		return (1);
	while (path[i])
	{
		if (path[i] == '0' || (path[i] == '.' && path[i + 1] == '\0')
			|| (path[i] == '.' && path[i + 1] == '.' && path[i + 2] == '\0'))
			break ;
		if (path[i] == '.' && (path[i + 1] == '/' || path[i + 1] == '\0'))
			i += 2;
		else if (path[i] == '.' && path[i + 1] == '.' && path[i + 2] == '/')
			i += 3;
		else
			return (0);
	}
	return (1);
}

static char	*handle_missingpwd(t_base *base, t_env *pwd, char *path, int *flag)
{
	char	*concatenated;
	char	*cwd;

	*flag = 1;
	if (pwd)
		cwd = pwd->value;
	else
		cwd = base->pwd_log;
	concatenated = ft_calloc(ft_strlen(cwd)
			+ ft_strlen(base->lst->arg[1]) + 2, sizeof(char));
	if (!concatenated)
	{
		base->exit_code = print_err_malloc();
		return (NULL);
	}
	ft_strcpy(concatenated, cwd);
	if (concatenated[ft_strlen(concatenated) - 1] != '/')
		ft_strcat(concatenated, "/");
	ft_strcat(concatenated, path);
	if (pwd)
	{
		if (update_pwd_in_missingpwd(base, pwd, concatenated) == 1)
			return (NULL);
	}
	return (concatenated);
}

static int	update_pwd_in_missingpwd(t_base *base, t_env *pwd, char *path)
{
	char	*tmp;

	tmp = pwd->value;
	pwd->value = ft_strdup(path);
	free(tmp);
	if (!pwd->value)
	{
		base->exit_code = print_err_malloc();
		return (1);
	}
	return (0);
}
