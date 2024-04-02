/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 08:53:04 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/02 14:34:49 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_chdir(char *path, t_base *base);
static int	update_pwd(t_env *pwd, t_env *oldpwd);

int	ft_cd(t_base *base)
{
	char	*path;

	if (base->lst->arg[1] == NULL || ft_strncmp(base->lst->arg[1], ".", 2) == 0
		|| ft_strncmp(base->lst->arg[1], "~", 2) == 0
		|| ft_strncmp(base->lst->arg[1], "~/", 3) == 0)
		path = get_path(base, "HOME");
	else if (ft_strncmp(base->lst->arg[1], "/", 2) == 0)
		path = ft_strdup("/");
	else if (ft_strncmp(base->lst->arg[1], "-", 2) == 0)
		path = get_path(base, "OLDPWD");
	else if (ft_strncmp(base->lst->arg[1], "..", 3) == 0)
		path = get_path_to_parentdir(base);
	else if (ft_strncmp(base->lst->arg[1], "./", 3) == 0)
		path = get_pwd();
	else
		path = ft_strdup(base->lst->arg[1]);
	if (!path)
		return (1);
	if (ft_chdir(path, base) == 1)
		return (ft_free((void *)path, 1));
	if (base->lst->arg[1] && ft_strncmp(base->lst->arg[1], "-", 2) == 0)
		printf("%s\n", path);
	return (ft_free((void *)path, 0));
}

static int	update_pwd(t_env *pwd, t_env *oldpwd)
{
	char	cwd[PWD_SIZE];
	char	*tmp;
	
	if (getcwd(cwd, sizeof(cwd)) == 0)
		return (1);
	tmp = oldpwd->value;
	oldpwd->value = pwd->value;
	free(tmp);
	pwd->value = ft_strdup(cwd);
	if (!pwd->value)
		return (ft_perror("malloc", 1));
	return (0);
}

static int	ft_chdir(char *path, t_base *base)
{
	t_env	*pwd;
	t_env	*oldpwd;

	pwd = find_env_var(base, "PWD");
	oldpwd = find_env_var(base, "OLDPWD");
	if (pwd == NULL || oldpwd == NULL)
		return (1);
	if (chdir(path) == -1)
	{
		ft_fprintf(2, "minishell: cd: %s: %s\n", base->lst->arg[1],
			strerror(errno));
			
		return (1);
	}
	if (update_pwd(pwd, oldpwd) == 1)
		return (1);
	return (0);
}

/*
cd ./
cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory

pwd
/home/yusengok/Documents/CommonCore/1-GitHub/42-Minishell/test/./

env | grep PWD
PWD=/home/yusengok/Documents/CommonCore/1-GitHub/42-Minishell/test/./
OLDPWD=/home/yusengok/Documents/CommonCore/1-GitHub/42-Minishell/test

cd ..
env | grep PWD
PWD=/home/yusengok/Documents/CommonCore/1-GitHub/42-Minishell
OLDPWD=/home/yusengok/Documents/CommonCore/1-GitHub/42-Minishell/test/./
*/