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

/*
bash-3.2$ pwd
/Users/yukosengoku/Documents/42/42-Minishell

bash-3.2$ mkdir test
bash-3.2$ cd test
bash-3.2$ pwd
/Users/yukosengoku/Documents/42/42-Minishell/test

bash-3.2$ rm -rf ../test
bash-3.2$ pwd
/Users/yukosengoku/Documents/42/42-Minishell/test

bash-3.2$ cd ./
cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
bash-3.2$ pwd
/Users/yukosengoku/Documents/42/42-Minishell/test/./
bash-3.2$ cd ..
bash-3.2$ pwd
/Users/yukosengoku/Documents/42/42-Minishell
*/

/*
bash-3.2$ env | grep PWD
PWD=/Users/yukosengoku/Documents/42/42-Minishell/test
OLDPWD=/Users/yukosengoku/Documents/42/42-Minishell
bash-3.2$ 
*/

static int	ft_chdir(char *path, t_base *base)
{
	char	cwd[PWD_SIZE];
	t_env	*pwd;
	t_env	*oldpwd;
	char	*tmp;

	if (chdir(path) == -1)
	{
		ft_fprintf(2, "minishell: cd: %s: %s\n", base->lst->arg[1],
		strerror(errno));
		return (EXIT_FAILURE);
	}
	pwd = find_env_var(base, "PWD");
	oldpwd = find_env_var(base, "OLDPWD");
	tmp = NULL;
	if (pwd == NULL || oldpwd == NULL)
		return (1);
	if (getcwd(cwd, sizeof(cwd)) != 0)
	{
		tmp = oldpwd->value;
		oldpwd->value = pwd->value;
		free(tmp);
		pwd->value = ft_strdup(cwd);
		if (!pwd->value)
			return (ft_perror("malloc", EXIT_FAILURE));
	}
	else
		chdir(pwd->value);
	return (0);
}
