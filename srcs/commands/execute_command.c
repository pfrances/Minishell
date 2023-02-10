/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 17:09:48 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/10 10:50:10 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process_job(t_cmd *cmd)
{
	set_signal_handling();
	execve(cmd->path, cmd->args, g_state.envp);
	perror(cmd->args[0]);
	exit(EXIT_FAILURE);
}

void	parent_process_job(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	actualise_exit_status(WEXITSTATUS(status));
}

void	execute_command(t_ast_node *cmd_node)
{
	pid_t	pid;

	cmd_node->cmd = init_cmd(cmd_node->token->lexem);
	if (g_state.error != NO_ERROR)
		return ;
	set_redirections(cmd_node->cmd);
	if (g_state.error != NO_ERROR)
		return (free_cmd(cmd_node->cmd));
	if (cmd_node->cmd->builtin_type != NOT_BUILTIN)
		execute_builtin(cmd_node->cmd);
	else
	{
		pid = fork();
		if (pid == 0)
			child_process_job(cmd_node->cmd);
		else if (pid > 0)
			parent_process_job(pid);
		else
		{
			perror("fork failed");
			g_state.error = FORK_FAILED;
		}
	}
	reset_redirections(cmd_node->cmd);
	free_cmd(cmd_node->cmd);
}
