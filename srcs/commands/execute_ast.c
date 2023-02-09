/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:13:39 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/09 17:06:41 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_ast(t_ast_node *node)
{
	if (g_state.error_state != NO_ERROR)
		return ;
	if (node->token->type == COMMAND)
		execute_command(node);
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
		if (g_state.exit_status != 0)
			execute_ast(node->right);
	}
	else if (node->token->type == AND)
	{
		execute_ast(node->left);
		if (g_state.exit_status == 0)
			execute_ast(node->right);
	}
}
