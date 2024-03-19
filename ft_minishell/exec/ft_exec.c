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
	/*------ if builtin && no pipe -----*/
	if (base->lst->next == NULL)
	{
		// if (ft_strcmp(base->lst->arg[0], CD) == 0)
		// 	ft_cd(); // to code
		if (ft_strcmp(base->lst->arg[0], ECHO) == 0)
			ft_echo(base->lst->arg, base->lst->write, base->lst->append); // not complete yet
		// else if (ft_strcmp(base->lst->arg[0], ENV) == 0)
		// 	ft_env(); // to code
		// else if (ft_strcmp(base->lst->arg[0], EXIT) == 0)
		// 	ft_exit(); // to code
		// else if (ft_strcmp(base->lst->arg[0], EXPORT) == 0)
		// 	ft_export(); // to code
		else if (ft_strcmp(base->lst->arg[0], PWD) == 0)
			ft_pwd(base); // not complete yet
		// else if (ft_strcmp(base->lst->arg[0], UNSET) == 0)
		// 	ft_unset(); // to code
	}
	/*------ if not builtin -----*/
	execute_commands(base);
	return (0);
}

static int	execute_commands(t_base *base)
{
	int		fd_in;
	int		fd_out;
	int		pipe[2];
	pid_t	child_pid;

	// init pipe: pipe[2]
	if (base->lst->read == NULL)
		fd_in = 0;
	while (base->lst)
	{
		// PIPE:
		//  READ_END
		if (base->lst->read != NULL)
			fd_in = open_input_file(base);
		// else --> fd_in from previous command

		//  WRITE_END
		if (base->lst->write != NULL)
			fd_out = open_output_file(base);
		else if (base->lst->write == NULL)
			fd_out = 1;
		else
			fd_out = pipe[WRITE_END];

		// FORK
		child_pid = ft_fork(&pipe);
		/*---child---*/
		if (child_pid == 0)
		{
			close(pipe[READ_END]);
			dup_input(fd_in); // STDIN -> fd_in
			dup_output(fd_out);
			// execve
		}
		/*---parent---*/
		else
		{
			close(pipe[WRITE_END]);
			ft_close(fd_in);
		}
		fd_in = pipe[READ_END];
	}
	ft_close(fd_in);
	return (0);
}
