/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:24:46 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/19 15:55:25 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_commands(t_base *base);

int	ft_exec(t_base *base)
{
	/*------ if builtin -----*/
	// if (ft_strncmp(base->lst->arg[0], CD, ft_strlen(CD)) == 0)
	// 	ft_cd(); // to code
	if (ft_strncmp(base->lst->arg[0], ECHO, ft_strlen(ECHO)) == 0)
		ft_echo(base->lst->arg, base->lst->write, base->lst->append); // need to modify
	// else if (ft_strncmp(base->lst->arg[0], ENV, ft_strlen(ENV)) == 0)
	// 	ft_env(); // to code
	// else if (ft_strncmp(base->lst->arg[0], EXIT, ft_strlen(CD)) == 0)
	// 	ft_exit(); // to code
	// else if (ft_strncmp(base->lst->arg[0], EXPORT, ft_strlen(EXPORT)) == 0)
	// 	ft_export(); // to code
	// else if (ft_strncmp(base->lst->arg[0], PWD, ft_strlen(PWD)) == 0)
	// 	ft_pwd(base); // need to modify
	// else if (ft_strncmp(base->lst->arg[0], UNSET, ft_strlen(UNSET)) == 0)
	// 	ft_unset(); // to code
	/*------ if not builtin -----*/
	else
		execute_commands(base);
	return (0);
}

static int	execute_commands(t_base *base)
{
	(void)base;
	// int	fd_in;
	// int	fd_out;

	// if (base->lst->next == NULL)
	// 	single_command_exec(); // to code
	// else
	// {
	// 	while (base->lst)
	// 	{
	// 		if (base->lst->read)
	// 			fd_in = open_input_file(base);
	// 	}
	// }
	return (0);
}
