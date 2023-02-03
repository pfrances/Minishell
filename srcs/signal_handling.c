/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:58:27 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/03 17:15:19 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_interrupt(int sig)
{
	(void)sig;
	if (g_state.wait_endline == true)
	{
		g_state.stop_signal_flag = true;
		rl_replace_line("", 0);
		rl_done = 1;
		write(STDOUT_FILENO, "\n", 1);
		// rl_on_new_line();
		//rl_redisplay();
	}
	else if (g_state.pgrm_is_running == false)
	{
		g_state.stop_signal_flag = true;
		rl_on_new_line();
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
	}
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

	sig_end_process_handler.sa_handler = process_interrupt;
	sig_ignoring_handler.sa_handler = ignore_signal;
	sigemptyset(&sig_end_process_handler.sa_mask);
	sigemptyset(&sig_ignoring_handler.sa_mask);
	sig_end_process_handler.sa_flags = 0;
	sig_ignoring_handler.sa_flags = 0;
	sigaction(SIGINT, &sig_end_process_handler, NULL);
	sigaction(SIGQUIT, &sig_ignoring_handler, NULL);
}
