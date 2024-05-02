/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 08:53:04 by yusengok          #+#    #+#             */
/*   Updated: 2024/05/02 23:25:51 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_home(char *arg);
static int	ft_chdir(char *curpath, t_line *node, int fd[2], int *missing_pwd);
static int	update_pwd(t_base *base, char *curpath);
static int	update_pwd(t_base *base, char *curpath);

int	ft_cd(t_base *base, t_line *node, int fd[2])
{
	char	*curpath;
	int		missing_pwd;

	missing_pwd = 0;
	if (node->arg[1] && node->arg[2])
		return (print_err(CD, "too many arguments", NULL, 1));
	if (is_home(node->arg[1]) == true || !ft_strncmp(node->arg[1], "-", 2))
		curpath = expand_path(base, node->arg[1]);
	else
		curpath = ft_strdup(node->arg[1]);
	if (!curpath)
		return (1);
	if (curpath[0] != '/')
		curpath = concatenate_path(base, curpath, &missing_pwd);
	if (!curpath)
		return (base->exit_code);
	canonicalize_path(curpath, node);
	if (ft_chdir(curpath, node, fd, &missing_pwd) == 1)
		return (ft_free((void *)curpath, 1));
	if (missing_pwd != 1)
		update_pwd(base, curpath);
	if (node->arg[1] && ft_strncmp(node->arg[1], "-", 2) == 0)
		ft_pwd(base, fd);
	ft_close(fd[IN], fd[OUT], 0);
	return (ft_free((void *)curpath, base->exit_code));
}

static bool	is_home(char *arg)
{
	if (arg == NULL || ft_strcmp(arg, "--") == 0)
		return (true);
	return (false);
}

static int	ft_chdir(char *curpath, t_line *node, int fd[2], int *missing_pwd)
{
	if (chdir(curpath) == -1)
	{
		if (*missing_pwd == 1)
			return (print_err("chdir", "error retrieving current directory: \
getcwd: cannot access parent directories", \
"No such file or directory", 0));
		ft_close(fd[IN], fd[OUT], 0);
		return (print_err(CD, node->arg[1], strerror(errno), 1));
	}
	*missing_pwd = 2;
	return (0);
}

static int	update_oldpwd(t_base *base, t_env *oldpwd)
{
	t_env	*pwd;
	char	*tmp;

	pwd = find_env_var(base, "PWD");
	if (oldpwd->value)
	{
		tmp = oldpwd->value;
		if (pwd && pwd->value)
			oldpwd->value = pwd->value;
		else
			oldpwd->value = ft_strdup(base->pwd_log);
		free(tmp);
		if (!oldpwd->value)
			return (ft_perror("malloc", 1));
	}
	else if (!oldpwd->value)
	{
		oldpwd->value = ft_strdup(base->pwd_log);
		if (!oldpwd->value)
			return (ft_perror("malloc", 1));
	}
	return (0);
}

static int	update_pwd(t_base *base, char *curpath)
{
	t_env	*oldpwd;
	t_env	*pwd;

	ft_strcpy(base->oldpwd_log, base->pwd_log);
	oldpwd = find_env_var(base, OLDPWD);
	if (!oldpwd)
		return (1);
	if (update_oldpwd(base, oldpwd) == 1)
		return (1);
	ft_strcpy(base->pwd_log, curpath);
	pwd = find_env_var(base, "PWD");
	if (pwd && pwd->value)
	{
		pwd->value = ft_strdup(curpath);
		if (!pwd->value)
			return (ft_perror("malloc", 1));
	}
	return (0);
}
