/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:58:27 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/14 13:32:35 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	readline_stop(void)
{
	if (g_state.stop_signal_flag == true)
	{
		rl_done = 1;
		rl_replace_line("", 0);
	}
	return (0);
}

void	process_interrupt(int sig)
{
	(void)sig;
	g_state.stop_signal_flag = true;
	if (g_state.current_phase == EXECUTING_CMD)
		write(STDOUT_FILENO, "\n", 1);
}

void	ignore_signal(int sig)
{
	(void)sig;
	return ;
}

void	set_signal_handling(void)
{
	struct sigaction	sig_end_process_handler;
	struct sigaction	sig_ignoring_handler;

	rl_event_hook = readline_stop;
	sig_end_process_handler.sa_handler = process_interrupt;
	sig_ignoring_handler.sa_handler = ignore_signal;
	sigemptyset(&sig_end_process_handler.sa_mask);
	sigemptyset(&sig_ignoring_handler.sa_mask);
	sig_end_process_handler.sa_flags = 0;
	sig_ignoring_handler.sa_flags = 0;
	sigaction(SIGINT, &sig_end_process_handler, NULL);
	sigaction(SIGQUIT, &sig_ignoring_handler, NULL);
}
