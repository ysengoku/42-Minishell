/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:34:48 by dvo               #+#    #+#             */
/*   Updated: 2024/04/12 16:14:02 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int received_signal;

static void	handle_sigint(int sig)
{
	(void)sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	received_signal = SIGINT;
}

static void	ft_minishell(t_base *base)
{
	char	*str;
	int		i;

	str = readline(CYAN "minishell >>> " RESET);
	if (str && *str)
	{
		add_history(str);
		if (ft_chara_split(str, &base) != -1)
			base->exit_code = ft_exec(base);
		else
			base->exit_code = 2;
		received_signal = 0;
		unlink_heredoc();
		free_base_content(base);
	}
	if (!str)
	{
		if (received_signal != 0)
			i = 128 + received_signal;
		else
			i = base->exit_code;
		free_base_content(base);
		write(1, "\n", 1);
		exit (i);
	}
	ft_free((void *)str, 0);
}

static int	command_line_mode(t_base *base, char *av2)
{
	int	exit_code;

	exit_code = 0;
	if (ft_chara_split(av2, &base) != -1)
		exit_code = ft_exec(base);
	else
		exit_code = 2;
	unlink_heredoc();
	free_base_content(base);
	free_envlist(base);
	free(base);
	return (exit_code);
}

int	main(int ac, char **av, char **env)
{
	t_base	*base;

	base = NULL;
	if (ac == 1)
	{
		base = ft_calloc(1, sizeof(t_base));
		if (!base)
			return (ft_perror("malloc", 1));
		base->env = env;
		base->exit_code = 0;
		assign_env(base);
		signal(SIGINT, handle_sigint);
		while (1)
		{
			ft_minishell(base);
			if (received_signal != 0)
			{
				base->exit_code = 128 + received_signal;
				received_signal = 0;
			}
		}
	}
	else if (ac == 3 && ft_strncmp(av[1], "-c", 2) == 0)
	{
		base = ft_calloc(1, sizeof(t_base));
		if (!base)
			return (ft_perror("malloc", 1));
		assign_env(base);
		return (command_line_mode(base, av[2]));
	}
	else
		return (print_err("Usage", COMMANDLINE_USAGE, NULL, 1));
}
