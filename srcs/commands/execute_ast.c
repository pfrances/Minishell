/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:13:39 by pfrances          #+#    #+#             */
/*   Updated: 2023/01/31 12:40:44 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_pipe(t_ast_node *node)
{
	int		fd[2];
	int		status;
	int		input_save;
	int		output_save;
	pid_t	pid;

	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		output_save = dup(STDOUT_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		execute_ast(node->left);
		close(fd[1]);
		dup2(output_save, STDOUT_FILENO);
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		close(fd[1]);
		input_save = dup(STDIN_FILENO);
		dup2(fd[0], STDIN_FILENO);
		status = execute_ast(node->right);
		close(fd[0]);
		dup2(input_save, STDIN_FILENO);
	}
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
