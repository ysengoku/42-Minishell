/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:34:48 by dvo               #+#    #+#             */
/*   Updated: 2024/03/27 13:58:43 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_sigint(int sig)
{
	(void) sig;
	printf(CYAN "\nminishell >>> "RESET);
}

static void	ft_minishell(t_base *base)
{
	char *str;
	
	str = readline(CYAN "minishell >>> " RESET);
	if (str && *str)
	{
		add_history(str);
		if (ft_chara_split(str, &base) != -1)
			base->exit_code = ft_exec(base); /// Use for $?
		else
			base->exit_code = 1;
		printf(RED "exit_code = %d\n" RESET, base->exit_code); ////////////// FOR TEST
		unlink_heredoc();
		free_base_content(base);
	}
	if (!str)
	{
		write(1, "\n", 1);
		exit (0);
	}
	ft_free((void *)str);
}

int	main(int ac, char **av, char **env)
{
	t_base	*base;

	base = ft_calloc(1, sizeof(t_base));
	if (!base)
		return (ft_perror("malloc", 1));
	base->env = env;
	base->exit_code = 0;
	assign_env(base, env);
	if (ac == 1)
	{
		signal(SIGINT, handle_sigint);
		while (1)
			ft_minishell(base);
	}
	else
	{
		(void) av;
		printf(RED "What to do if there is arguments ?\n" RESET);
	}
	free_envlist(base);
	free(base);
	return (0);
}
