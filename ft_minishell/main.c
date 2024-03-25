/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:34:48 by dvo               #+#    #+#             */
/*   Updated: 2024/03/24 22:24:19 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_sigint(int sig) 
{ 
	(void) sig;
    printf(CYAN "\nminishell >>> "RESET); 
}

int	main(int ac, char **av, char **env)
{
	char 	*str;
	t_base	*base;

	base = ft_calloc(1, sizeof(t_base));
	base->env = env;
	(void) ac;
	(void) av;
	assign_env(base, env);
	signal(SIGINT, handle_sigint);
	while(1)
	{
		str = readline(CYAN "minishell >>> " RESET);
		if (str && *str)
		{
			add_history(str);
			if (ft_chara_split(str, &base) != -1)
				ft_exec(base);
		}
		else
		{
			write(1, "\n", 1);
			exit (0);
		}
	}
}
