/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 17:09:48 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/15 13:32:38 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process_job(t_cmd *cmd)
{
	set_signal_handling();
	execve(cmd->path, cmd->args, g_state.envp);
	perror(cmd->args[0]);
	exit(errno);
}

void	execute_command(t_ast_node *node)
{
	pid_t	pid;
	int		status;

	if (init_cmd(node) == false)
		return ;
	status = 0;
	set_redirections(node->cmd);
	if (node->cmd->builtin_type != NOT_BUILTIN)
		execute_builtin(node->cmd);
	else if (node->cmd->path != NULL)
	{
		pid = fork();
		if (pid == 0)
			child_process_job(node->cmd);
		else if (pid > 0)
			waitpid(pid, &status, 0);
		else
		{
			perror("fork failed");
			g_state.error = FORK_FAILED;
		}
	}
	actualise_exit_status(WEXITSTATUS(status));
	reset_redirections(node->cmd);
}
