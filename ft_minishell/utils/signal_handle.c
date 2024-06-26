/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:19:11 by dvo               #+#    #+#             */
/*   Updated: 2024/05/02 18:45:39 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_received_signal = sig;
}

void	exec_sigint(int sig)
{
	g_received_signal = sig;
}

void	exec_sigquit(int sig)
{
	g_received_signal = sig;
}

static void	here_doc_sigint(int sig, siginfo_t *info, void *arg)
{
	(void)arg;
	(void)info;
	g_received_signal = sig;
	write(0, "\n", 1);
}

void	set_heredoc_signal(void)
{
	struct sigaction	act;
	struct sigaction	act_quit;

	ft_bzero(&act_quit, sizeof(struct sigaction));
	ft_bzero(&act, sizeof(struct sigaction));
	act_quit.sa_handler = SIG_IGN;
	sigemptyset(&act_quit.sa_mask);
	act_quit.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	act.sa_sigaction = here_doc_sigint;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act_quit, NULL);
}
