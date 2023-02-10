/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:42:33 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/10 10:36:46 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*create_node(t_lexer *lexer)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (node == NULL)
	{
		g_state.error = MALLOC_FAILED;
		return (NULL);
	}
	node->token = lexer->current_token;
	node->cmd = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}
