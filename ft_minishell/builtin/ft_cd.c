/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 08:53:04 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/15 13:14:15 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_home(char *arg);
static int	ft_chdir(char *curpath, t_base *base, t_line *node, int fd[2]);
static int	retry_cwd(t_base *base);

int	ft_cd(t_base *base, t_line *node, int fd[2])
{
	char	*curpath;

	if (node->arg[1] && node->arg[2])
		return (print_err(CD, "too many arguments", NULL, 1));
	if (is_home(node->arg[1]) == true)
		curpath = get_path(base, "HOME");
	else if (ft_strncmp(node->arg[1], "-", 2) == 0)
		curpath = get_path(base, "OLDPWD");
	else
		curpath = ft_strdup(node->arg[1]);
	if (!curpath)
		return (1);
	if (curpath[0] != '/')
		curpath = concatenate_path(base, curpath);
	if (!curpath)
		return (base->exit_code);
	canonicalize_path(curpath, node);
	if (ft_chdir(curpath, base, node, fd) == 1)
		return (ft_free((void *)curpath, 1));
	else if (node->arg[1] && ft_strncmp(node->arg[1], "-", 2) == 0)
		ft_putendl_fd(curpath, fd[OUT]);
	ft_close(fd[IN], fd[OUT], 0);
	return (ft_free((void *)curpath, 0));
}

char	*ft_strstr_r(char *big, char *little)
{
	int	i;
	int	j;

	i = ft_strlen(big) - ft_strlen(little);
	if (i < 0)
		return (big);
	j = 0;
	while (big[i] && little[j])
	{
		if (big[i] != little[j])
			return (&big[i]);
		i++;
		j++;
	}
	return (NULL);
}

static int	ft_chdir(char *curpath, t_base *base, t_line *node, int fd[2])
{
	t_env	*pwd;
	t_env	*oldpwd;
	char	*tmp;

	pwd = find_env_var(base, "PWD");
	if (pwd == NULL)
		return (print_err(CD, "PWD not set", NULL, 1));
	oldpwd = find_env_var(base, "OLDPWD");
	if (oldpwd == NULL)
		return (print_err(CD, "OLDPWD not set", NULL, 1));
	if (chdir(curpath) == -1)
	{
		ft_close(fd[IN], fd[OUT], 0);
		if (!ft_strcmp(node->arg[1], ".."))
			return (print_err("chdir", DELETED_CWD, NULL, 0));
		else if (!ft_strstr_r(node->arg[1], "./")
			|| !ft_strstr_r(node->arg[1], "."))
			return (retry_cwd(base));
		else
		return (print_err(CD, node->arg[1], strerror(errno), 1));
	}
	tmp = oldpwd->value;
	oldpwd->value = pwd->value;
	free(tmp);
	pwd->value = ft_strdup(curpath);
	if (!pwd->value)
		return (ft_perror("malloc", 1));
	return (0);
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
		return (print_err("chdir", DELETED_CWD, NULL, 1));
	}
	return (chdir(buf));
}

static bool	is_home(char *arg)
{
	if (arg == NULL || ft_strncmp(arg, "~", 2) == 0
		|| ft_strncmp(arg, "~/", 3) == 0)
		return (true);
	return (false);
}
