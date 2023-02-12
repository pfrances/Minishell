/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 17:28:16 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/10 16:30:29 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_left_pipe(t_ast_node *node, int fd[])
{
	int	output_save;

	close(fd[0]);
	output_save = dup(STDOUT_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	execute_ast(node->left);
	close(fd[1]);
	dup2(output_save, STDOUT_FILENO);
	exit(0);
}

void	execute_right_pipe(pid_t pid, t_ast_node *node, int fd[])
{
	int	input_save;
	int	status;

	waitpid(pid, &status, 0);
	actualise_exit_status(WEXITSTATUS(status));
	close(fd[1]);
	input_save = dup(STDIN_FILENO);
	dup2(fd[0], STDIN_FILENO);
	execute_ast(node->right);
	close(fd[0]);
	dup2(input_save, STDIN_FILENO);
}

void	execute_pipe(t_ast_node *node)
{
	int		fd[2];
	pid_t	pid;

	if (g_state.error != NO_ERROR)
		return ;
	if (pipe(fd) == -1)
	{
		g_state.error = PIPE_FAILED;
		return ;
	}
	pid = fork();
	if (pid == 0)
		execute_left_pipe(node, fd);
	else if (pid > 0)
		execute_right_pipe(pid, node, fd);
	else
		g_state.error = FORK_FAILED;
}
