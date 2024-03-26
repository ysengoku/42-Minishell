/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:34:48 by dvo               #+#    #+#             */
/*   Updated: 2024/03/26 16:32:14 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	(void) sig;
	printf(CYAN "\nminishell >>> "RESET);
}

int	main(int ac, char **av, char **env)
{
	char	*str;
	t_base	*base;

	base = ft_calloc(1, sizeof(t_base));
	if (!base)
		return (print_error("malloc", "memory allocation failed", EXIT_FAILURE));
	base->env = env;
	base->exit_status = 0;
	(void) ac;
	(void) av;
	assign_env(base, env);
	signal(SIGINT, handle_sigint);
	while (1)
	{
		str = readline(CYAN "minishell >>> " RESET);
		if (str && *str)
		{
			add_history(str);
			if (ft_chara_split(str, &base) != -1)
				base->exit_status = ft_exec(base); /// Use for $?
			printf(RED "exit_status = %d\n" RESET, base->exit_status); ////////////// FOR TEST
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
	rl_clear_history();
	ft_free((void *)str);
	free_envlist(base);
	free(base);
	return (0);
}
