/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:34:48 by dvo               #+#    #+#             */
/*   Updated: 2024/04/04 23:39:32 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_sigint(int sig)
{
	(void) sig;
	rl_replace_line("" , 0);
	rl_on_new_line();
	rl_redisplay();
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
			base->exit_code = 1;
		printf(RED "exit_code = %d\n" RESET, base->exit_code); /////// FOR TEST
		unlink_heredoc();
		free_base_content(base);
	}
	if (!str)
	{
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
		exit_code = 1;
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
		assign_env(base, env);
		signal(SIGINT, handle_sigint);
		while (1)
			ft_minishell(base);
	}
	else if (ac == 3 && ft_strncmp(av[1], "-c", 2) == 0)
	{
		base = ft_calloc(1, sizeof(t_base));
		if (!base)
			return (ft_perror("malloc", 1));
		assign_env(base, env);
		return (command_line_mode(base, av[2]));
	}
	else
		return (print_error("Usage", COMMANDLINE_USAGE, 1));
}
