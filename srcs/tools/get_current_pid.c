/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_current_pid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 20:52:12 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/09 21:29:07 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_current_pid_str(void)
{
	pid_t	pid;
	char	*pid_str;

	pid = fork();
	if (pid == 0)
		exit(0);
	else if (pid > 0)
	{
		waitpid(pid, NULL, 0);
		pid_str = ft_itoa(pid);
		if (pid_str == NULL)
			g_state.error_state = ALLOCATION_FAILED;
		return (pid_str);
	}
	perror("fork failed");
	g_state.error_state = FORK_FAILED;
	return (NULL);
}
