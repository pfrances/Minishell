/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:13:39 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/07 16:29:06 by pfrances         ###   ########.fr       */
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

void	execute_right_pipe(t_ast_node *node, int fd[])
{
	int	input_save;

	wait(NULL);
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

	if (g_state.error_state != NO_ERROR)
		return ;
	if (pipe(fd) == -1)
	{
		g_state.error_state = PIPE_FAILED;
		return ;
	}
	pid = fork();
	if (pid == 0)
		execute_left_pipe(node, fd);
	else if (pid > 0)
		execute_right_pipe(node, fd);
	else
		g_state.error_state = FORK_FAILED;
}

void	execute_ast(t_ast_node *node)
{
	if (g_state.error_state != NO_ERROR)
		return ;
	if (node->token->type == COMMAND)
		execute_command(node->cmd);
	else if (node->token->type == PIPE)
		execute_pipe(node);
	else if (node->token->type == SEMICOLON)
	{
		execute_ast(node->left);
		execute_ast(node->right);
	}
	else if (node->token->type == OR)
	{
		execute_ast(node->left);
		if (g_state.last_pgrm_exit_status != 0)
			execute_ast(node->right);
	}
	else if (node->token->type == AND)
	{
		execute_ast(node->left);
		if (g_state.last_pgrm_exit_status == 0)
			execute_ast(node->right);
	}
}
