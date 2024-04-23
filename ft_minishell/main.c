/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:34:48 by dvo               #+#    #+#             */
/*   Updated: 2024/04/23 12:47:00 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_received_signal = 0;

static void	ft_minishell(t_base *base)
{
	char	*str;
	int		exit_code;

	str = readline(CYAN "minishell >>> " RESET);
	if (str && *str)
	{
		add_history(str);
		if (ft_chara_split(str, &base) != -1)
			base->exit_code = ft_exec(base);
		else
			base->exit_code = 2;
		unlink_heredoc();
		free_base_content(base);
	}
	if (!str)
	{
		if (g_received_signal != 0)
			exit_code = 128 + g_received_signal;
		else
			exit_code = base->exit_code;
		free_base_content(base);
		exit (exit_code);
	}
	ft_free((void *)str, 0);
}

static int	command_line_mode(t_base *base, char *av2, char **env)
{
	int	exit_code;

	exit_code = 0;
	base = init_base(env);
	if (!base)
		return (1);
	if (assign_env(base) == -1)
	{
		free(base);
		return (1);
	}
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

	if (env && *env)
		check_shell_level(env);
	base = NULL;
	if (ac == 1)
	{
		base = init_base(env);
		if (!base)
			return (1);
		if (assign_env(base) == -1)
		{
			free (base);
			return (1);
		}
		while (1)
		{
			signal(SIGINT, handle_sigint);
			signal(SIGQUIT, SIG_IGN);
			ft_minishell(base);
		}
	}
	else if (ac == 3 && ft_strncmp(av[1], "-c", 2) == 0)
		return (command_line_mode(base, av[2], env));
	return (print_err("Usage", COMMANDLINE_USAGE, NULL, 1));
}
