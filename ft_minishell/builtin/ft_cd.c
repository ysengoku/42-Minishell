/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 08:53:04 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/16 16:35:12 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_home(char *arg);
static char	*get_path(t_base *base, char *arg);
static char	*get_oldpwd_path(t_base *base);
static int	ft_chdir(char *curpath, t_line *node, int fd[2], int *missing_pwd);
static void	update_pwd(t_base *base, char *curpath);

int	ft_cd(t_base *base, t_line *node, int fd[2])
{
	char	*curpath;
	int		missing_pwd;

	missing_pwd = 0;
	if (node->arg[1] && node->arg[2])
		return (print_err(CD, "too many arguments", NULL, 1));
	if (is_home(node->arg[1]) == true || !ft_strncmp(node->arg[1], "-", 2))
		curpath = get_path(base, node->arg[1]);
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
	if (node->arg[1] && ft_strncmp(node->arg[1], "-", 2) == 0)
		ft_putendl_fd(curpath, fd[OUT]);
	if (missing_pwd != 1)
		update_pwd(base, curpath);
	ft_close(fd[IN], fd[OUT], 0);
	return (ft_free((void *)curpath, base->exit_code));
}

static bool	is_home(char *arg) /// If we expand '~', we can remove this function
{
	if (arg == NULL || ft_strncmp(arg, "~", 2) == 0
		|| ft_strncmp(arg, "~/", 3) == 0)
		return (true);
	return (false);
}

static char	*get_oldpwd_path(t_base *base)
{
	t_env	*oldpwd;
	char	*path;

	oldpwd = find_env_var(base, OLDPWD);
	if (!oldpwd || !oldpwd->value)
	{
		if (base->oldpwd_log[0] == 0)
		{
			ft_fprintf(2, "minishell: cd: %s not set\n", OLDPWD);
			return (NULL);
		}
		path = ft_strdup(base->oldpwd_log);
		if (!path)
			ft_perror("malloc", 1);
		return (path);
	}
	path = ft_strdup(oldpwd->value);
	if (!path)
		perror("malloc");
	return (path);
}

static char	*get_path(t_base *base, char *arg)
{
	char	*path;

	path = NULL;
	if (arg == NULL)
	{
		if (!find_env_var(base, HOME) || !find_env_var(base, HOME)->value)
		{
			ft_fprintf(2, "minishell: cd: %s not set\n", HOME);
			return (NULL);
		}
		path = ft_strdup(getenv(HOME));
		if (!path)
			ft_perror("malloc", 1);
	}
	else if (ft_strncmp(arg, "~", 2) == 0 || ft_strncmp(arg, "~/", 3) == 0)
	{
		path = ft_strdup(getenv(HOME));
		if (!path)
			ft_perror("malloc", 1);
	}
	else if (ft_strncmp(arg, "-", 2) == 0)
		path = get_oldpwd_path(base);
	return (path);
}

static int	ft_chdir(char *curpath, t_line *node, int fd[2], int *missing_pwd)
{
	if (chdir(curpath) == -1)
	{
		if (*missing_pwd == 1)
			return (print_err("chdir", DELETED_CWD, NULL, 0));
		ft_close(fd[IN], fd[OUT], 0);
		return (print_err(CD, node->arg[1], strerror(errno), 1));
	}
	*missing_pwd = 2;
	return (0);
}

static void	update_pwd(t_base *base, char *curpath)
{
	t_env	*pwd;
	t_env	*oldpwd;
	char	*tmp;

	pwd = find_env_var(base, "PWD");
	oldpwd = find_env_var(base, OLDPWD);
	ft_strcpy(base->oldpwd_log, pwd->value);
	if (oldpwd == NULL)
	{
		tmp = pwd->value;
		pwd->value = ft_strdup(curpath);
		free(tmp);
		return ;
	}
	else
	{
		tmp = oldpwd->value;
		oldpwd->value = pwd->value;
		free(tmp);
		pwd->value = ft_strdup(curpath);
	}
	if (!pwd->value)
		base->exit_code = (ft_perror("malloc", 1));
	else
		base->exit_code = 0;
}
