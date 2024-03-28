/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:34:48 by dvo               #+#    #+#             */
/*   Updated: 2024/03/28 11:48:59 by yusengok         ###   ########.fr       */
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
	char	*str;

	str = readline(CYAN "minishell >>> " RESET);
	if (str && *str)
	{
		add_history(str);
		if (ft_chara_split(str, &base) != -1)
			base->exit_code = ft_exec(base);
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
	ft_free((void *)str, 0);
}

/*
bash -c "ls"
ft_minishell  in  lib  Makefile  README.md

bash -c << EOF 'cat'
> hello
> coucou
> EOF
hello
coucou

bash -c < in "cat"
Hello
Hello
Coucou
Hello
Coucou
Bonjour

bash -c "<< EOF cat"
bash: warning: here-document at line 0 delimited by end-of-file (wanted `EOF')

---> ./minishell -c "command"
The -c option is used to tell the Bash shell to execute the command that follows it
*/

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
	else if (ac > 2 && ft_strcmp(av[1], "-c") == 0)
	{
		if ((ft_strcmp(av[2], "<") == 0 || (ft_strcmp(av[2], "<<") == 0 && av[3])
			|| ft_strcmp(av[2], ">") == 0 || ft_strcmp(av[2], ">>") == 0 ) && av[3])
		{
			// check redirection (av[3] = file or delimiter)
			// if (av[4])
			// execute av[4] with here_doc as infile
			// else
			// error "minishell: -c: option requires an argument"
		}
		// else
		// execute av[2] & ignore arguments after av[3]
	}
	else // cases without option '-c'
	{
		// if av[1] == existing command (e.g. ls): error
		// "/usr/bin/ls: /usr/bin/ls: cannot execute binary file"
		
		// if av[1] == existing file (e.g. in): error 
		// in: line 1: Hello: command not found
		// in: line 2: Hello: command not found
		// in: line 3: Coucou: command not found...

		// if av[1] == non existing file: error
		// bash: (fine name): No such file or directory

		// arguments after av[2] are ignored
	}
	free_envlist(base);
	free(base);
	return (0);
}

