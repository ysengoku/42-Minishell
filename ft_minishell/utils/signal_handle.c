/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:19:11 by dvo               #+#    #+#             */
/*   Updated: 2024/04/19 18:15:16 by yusengok         ###   ########.fr       */
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

void	handle_sigint_inexec(int sig)
{
	g_received_signal = sig;
}

static void	here_doc_sig(int sig, siginfo_t *info, void *arg)
{
	(void)arg;
	(void)info;
	g_received_signal = sig;
	write(0, "\n", 1);
}

void	set_heredoc_signal(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(struct sigaction));
	sigemptyset(&act.sa_mask);
	act.sa_sigaction = here_doc_sig;
	sigaction(SIGINT, &act, NULL);
}
