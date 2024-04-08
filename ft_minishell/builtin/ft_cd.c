/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 08:53:04 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/08 10:09:29 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_home(char *arg);
static int	ft_chdir(char *curpath, t_base *base);
static int	retry_cwd(t_base *base);

int	ft_cd(t_base *base, t_line *node, int fd[2])
{
	char	*curpath;

	ft_close(fd[IN], fd[OUT], 0);
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
		return (1);
	canonicalize_path(curpath);
	if (!curpath)
		return (ft_free((void *)curpath, 0));
	if (ft_chdir(curpath, base) == 1)
		return (ft_free((void *)curpath, 1));
	if (node->arg[1] && ft_strncmp(node->arg[1], "-", 2) == 0 && fd[OUT] == 1)
		printf("%s\n", curpath);
	return (ft_free((void *)curpath, 0));
}

static int	ft_chdir(char *curpath, t_base *base)
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
		return (print_err(CD, DELETED_CWD, NULL, 1));
	}
	return (chdir(buf));
}

static bool	is_home(char *arg)
{
	if (arg == NULL || ft_strncmp(arg, ".", 2) == 0
		|| ft_strncmp(arg, "~", 2) == 0
		|| ft_strncmp(arg, "~/", 3) == 0)
		return (true);
	return (false);
}
