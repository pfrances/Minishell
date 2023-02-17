/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 17:09:48 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/17 16:27:04 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process_job(t_cmd *cmd)
{
	set_signal_handling();
	execve(cmd->path, cmd->args, g_state.envp);
	perror(cmd->args[0]);
	exit(1);
}

void	create_and_execute_process(t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0)
		child_process_job(cmd);
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
	{
		perror("fork failed");
		g_state.error = FORK_FAILED;
	}
	if (g_state.stop_signal_flag == true)
		g_state.stop_signal_flag = false;
	else
		actualise_exit_status(WEXITSTATUS(status));
}

void	execute_command(t_ast_node *node)
{
	if (init_cmd(node) == false || node->cmd->cmd_type == EMPTY_CMD)
		return ;
	set_redirections(node->cmd);
	if (node->cmd->cmd_type != NOT_BUILTIN)
		execute_builtin(node->cmd);
	else
		create_and_execute_process(node->cmd);
	reset_redirections(node->cmd);
}
