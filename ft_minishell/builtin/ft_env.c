/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 18:03:21 by dvo               #+#    #+#             */
/*   Updated: 2024/04/22 11:08:57 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	update_env_lastcommand(t_base *base);

int	ft_env(t_base *base, t_line *node, int fd[2])
{
	t_env	*tmp;

	if (node->arg[1])
	{
		ft_fprintf(2, "env: '%s': No such file or directory\n", node->arg[1]);
		return (127);
	}
	// update_env_lastcommand(base);
	tmp = base->envn;
	while (tmp)
	{
		if (tmp->value)
		{
			if (tmp->unset == 0)
			{
				ft_putstr_fd(tmp->key, fd[OUT]);
				write(fd[OUT], "=", 1);
				ft_putendl_fd(tmp->value, fd[OUT]);
			}
		}
		tmp = tmp->next;
	}
	ft_close(fd[IN], fd[OUT], 0);
	return (0);
}

// static void	update_env_lastcommand(t_base *base)
// {
// 	t_env	*tgt;
// 	char	*tmp;
// 	char	pwd[PATH_MAX];
	
// 	tgt = find_env_var(base, "_");
// 	if (!tgt)
// 		return ;
// 	tmp = tgt->value;
// 	getcwd(pwd, PATH_MAX);
// 	tgt->value = ft_calloc(ft_strlen(pwd) + ft_strlen(FTENV) + 1, sizeof(char));
// 	if (tgt->value)
// 		tgt->value = tmp;
// 	else
// 	{
// 		ft_strcpy(tgt->value, pwd);
// 		ft_strcat(tgt->value, FTENV);
// 		free(tmp);
// 	}
// }
