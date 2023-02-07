/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:44:33 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/07 16:34:03 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(void **array)
{
	size_t	i;

	if (array == NULL)
		return ;
	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_cmd(t_cmd *cmd)
{
	size_t	i;

	free_array((void **)cmd->args);
	i = 0;
	while (cmd->input_output[i] != NULL)
	{
		free(cmd->input_output[i]->filename);
		free(cmd->input_output[i]);
		i++;
	}
	free(cmd->input_output);
	free(cmd->path);
	free(cmd);
}

void	free_syntax_tree(t_ast_node *node)
{
	if (node == NULL)
		return ;
	free_syntax_tree(node->left);
	free_syntax_tree(node->right);
	if (node->token->type == COMMAND)
		free_cmd(node->cmd);
	free(node);
}

void	free_lexer_list(t_lexer_node *list)
{
	t_lexer_node	*trv;

	while (list != NULL)
	{
		trv = list->next;
		free(list->token.lexem);
		list->token.lexem = NULL;
		free(list);
		list = trv;
	}
}

void	free_all(t_lexer *lexer, t_ast_node *ast_root)
{
	free_syntax_tree(ast_root);
	if (g_state.error_state >= ALLOCATION_FAILED)
	{
		free_array((void **)lexer->tkn_types_array);
		free_array((void **)lexer->all_path);
		free(g_state.last_pgrm_exit_status_str);
		free(g_state.main_pid_str);
	}
	free_lexer_list(lexer->list_head);
	free(lexer->input);
}
