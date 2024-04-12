/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:34:48 by dvo               #+#    #+#             */
/*   Updated: 2024/04/12 17:56:48 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_received_signal;

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
		unlink_heredoc();
		free_base_content(base);
	}
	if (!str)
	{
		if (g_received_signal != 0)
			i = 128 + g_received_signal;
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

	g_received_signal = 0;
	if (ac == 1)
	{
		base = init_base(env);
		if (!base)
			return (1);
		assign_env(base);
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, handle_sigquit);
		while (1)
			ft_minishell(base);
	}
	else if (ac == 3 && ft_strncmp(av[1], "-c", 2) == 0)
	{
		base = init_base(env);
		if (!base)
			return (1);
		assign_env(base);
		return (command_line_mode(base, av[2]));
	}
	return (print_err("Usage", COMMANDLINE_USAGE, NULL, 1));
}
