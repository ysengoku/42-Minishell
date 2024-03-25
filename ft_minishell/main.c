/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:34:48 by dvo               #+#    #+#             */
/*   Updated: 2024/03/25 14:53:49 by yusengok         ###   ########.fr       */
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
	char	*str;
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
			free(str);	
			unlink_heredoc();
			// free_base(base);
		}
		else
		{
			write(1, "\n", 1);
			exit (0);
		}
		free_base_content(base);
	}
	free(base);
	return (0);
}
