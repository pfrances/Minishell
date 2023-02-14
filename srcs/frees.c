/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:44:33 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/14 15:36:48 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_cmd *cmd)
{
	size_t	i;

	if (cmd == NULL)
		return ;
	free_array((void **)cmd->args);
	i = 0;
	while (cmd->redirect[i] != NULL)
	{
		free(cmd->redirect[i]->filename);
		free(cmd->redirect[i]);
		i++;
	}
	free(cmd->redirect);
	free(cmd->path);
	free(cmd);
}

void	free_syntax_tree(t_ast_node *node)
{
	if (node == NULL)
		return ;
	free_syntax_tree(node->left);
	free_syntax_tree(node->right);
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
	if (g_state.error >= MALLOC_FAILED)
	{
		free_array((void **)lexer->tkn_types_array);
		free_array((void **)g_state.envp);
		free(g_state.exit_status_str);
	}
	free_lexer_list(lexer->list_head);
	free(lexer->input);
}
