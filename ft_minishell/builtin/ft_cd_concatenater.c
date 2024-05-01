/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_concatenater.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 08:26:03 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/19 07:49:57 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_dot_or_dotdot(char *path);
static char	*handle_missingpwd(t_base *base, t_env *pwd, char *path, int *flag);
static int	update_pwd_in_missingpwd(t_base *base, t_env *pwd, char *path);

char	*concatenate_path(t_base *base, char *curpath, int *missing_pwd)
{
	t_env	*pwd;
	char	*cwd;
	char	buf[PATH_MAX];
	char	*concatenated;

	cwd = getcwd(buf, sizeof(buf));
	pwd = find_env_var(base, "PWD");
	if (cwd == NULL && is_dot_or_dotdot(curpath) == 1)
		return (handle_missingpwd(base, pwd, curpath, missing_pwd));
	else
	{
		concatenated = ft_calloc(ft_strlen(buf)
				+ ft_strlen(base->lst->arg[1]) + 2, sizeof(char)); //ok
		if (!concatenated)
		{
			base->exit_code = print_err_malloc();
			return (NULL);
		}
		ft_strcpy(concatenated, buf);
		if (concatenated[ft_strlen(concatenated) - 1] != '/')
			ft_strcat(concatenated, "/");
		ft_strcat(concatenated, curpath);
	}
	free(curpath);
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
			+ ft_strlen(base->lst->arg[1]) + 2, sizeof(char)); //ok
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