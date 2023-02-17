/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 23:19:40 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/17 10:37:34 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_up_pipeline(t_ast_node *node)
{
	if (g_state.error != NO_ERROR)
		return ;
	if (node->token->type == COMMAND)
		init_cmd(node);
	else if (node->token->type == PIPE)
	{
		set_up_pipeline(node->left);
		set_up_pipeline(node->right);
	}
}

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

	close(fd[1]);
	input_save = dup(STDIN_FILENO);
	dup2(fd[0], STDIN_FILENO);
	execute_ast(node->right);
	close(fd[0]);
	dup2(input_save, STDIN_FILENO);
	waitpid(pid, &status, 0);
	actualise_exit_status(WEXITSTATUS(status));
}

void	execute_pipeline(t_ast_node *node)
{
	int		fd[2];
	pid_t	pid;

	set_up_pipeline(node);
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
