/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 08:53:04 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/28 08:31:21 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ft_chdir(char *path, t_base *base);
static t_env	*find_oldpwd(t_base *base);

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
		path = get_path_to_parentdir();
	else if (ft_strncmp(base->lst->arg[1], "./", 3) == 0)
		path = get_pwd();
	else
		path = ft_strdup(base->lst->arg[1]);
	if (!path)
		return (1);
	if (ft_chdir(path, base) == 1)
		return (ft_free((void *)path, 1));
	if (ft_strncmp(base->lst->arg[1], "-", 2) == 0)
		printf("%s\n", path);
	return (ft_free((void *)path, 0));
}

/*
yusengok@z1r9p1:~/Documents/CommonCore/1-GitHub/42-Minishell/test$ pwd
/home/yusengok/Documents/CommonCore/1-GitHub/42-Minishell/test

yusengok@z1r9p1:~/Documents/CommonCore/1-GitHub/42-Minishell/test$ rm -r test
rm: cannot remove 'test': No such file or directory
---> delete it on finder

yusengok@z1r9p1:~/Documents/CommonCore/1-GitHub/42-Minishell/test$ cd ./

yusengok@z1r9p1:~/.local/share/Trash/files/test$ cd -
bash: cd: /home/yusengok/Documents/CommonCore/1-GitHub/42-Minishell/test: No such file or directory
*/

static int	ft_chdir(char *path, t_base *base)
{
	char	next_oldpwd[PWD_SIZE];
	t_env	*oldpwd;
	char	*tmp;

	oldpwd = find_oldpwd(base);
	if (oldpwd == NULL)
		return (print_error(CD, "OLDPWD not found", 1));
	if (getcwd(next_oldpwd, sizeof(next_oldpwd)) == 0)
		return (ft_perror("getcwd", EXIT_FAILURE));
	if (chdir(path) == -1)
	{
		ft_fprintf(2, "minishell: cd: %s: %s\n", base->lst->arg[1],
			strerror(errno));
		return (EXIT_FAILURE);
	}
	tmp = oldpwd->value;
	oldpwd->value = ft_strdup(next_oldpwd);
	if (!oldpwd->value)
		return (ft_perror("malloc", EXIT_FAILURE));
	free(tmp);
	return (0);
}

static t_env	*find_oldpwd(t_base *base)
{
	t_env	*oldpwd;

	oldpwd = base->envn;
	while (oldpwd)
	{
		if (ft_strcmp(oldpwd->key, "OLDPWD") == 0)
			break ;
		oldpwd = oldpwd->next;
	}
	return (oldpwd);
}
