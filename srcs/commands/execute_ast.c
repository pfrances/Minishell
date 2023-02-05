/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:13:39 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/05 13:58:46 by pfrances         ###   ########.fr       */
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

int	execute_right_pipe(t_ast_node *node, int pid, int fd[])
{
	int	status;
	int	input_save;

	waitpid(pid, &status, 0);
	close(fd[1]);
	input_save = dup(STDIN_FILENO);
	dup2(fd[0], STDIN_FILENO);
	status = execute_ast(node->right);
	close(fd[0]);
	dup2(input_save, STDIN_FILENO);
	return (status);
}

int	execute_pipe(t_ast_node *node)
{
	int		fd[2];
	int		status;
	pid_t	pid;

	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid == 0)
		execute_left_pipe(node, fd);
	else
		status = execute_right_pipe(node, pid, fd);
	return (status);
}

int	execute_ast(t_ast_node *node)
{
	int	status;

	status = 0;
	if (node->token->type == COMMAND)
		status = execute_command(node->cmd);
	else if (node->token->type == PIPE)
		status = execute_pipe(node);
	else if (node->token->type == SEMICOLON)
	{
		status = execute_ast(node->left);
		status = execute_ast(node->right);
	}
	else if (node->token->type == OR)
	{
		status = execute_ast(node->left);
		if (status != 0)
			status = execute_ast(node->right);
	}
	else if (node->token->type == AND)
	{
		status = execute_ast(node->left);
		if (status == 0)
			status = execute_ast(node->right);
	}
	return (status);
}
