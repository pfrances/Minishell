/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_nodes1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:11:49 by pfrances          #+#    #+#             */
/*   Updated: 2023/01/08 16:13:42 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast_node	*parse_pipe(t_ast_node *root, t_lexer_node **lexer_list)
{
	t_ast_node	*new_node;

	root = parse_input_output(root, lexer_list);
	while ((*lexer_list) != NULL
		&& (*lexer_list)->token.type == TOKEN_PIPE)
	{
		new_node = create_node((*lexer_list)->token);
		new_node->left = root;
		*lexer_list = (*lexer_list)->next;
		new_node->right = parse_input_output(root, lexer_list);
		root = new_node;
	}
	return (root);
}

t_ast_node	*parse_and_or(t_ast_node *root, t_lexer_node **lexer_list)
{
	t_ast_node	*new_node;

	root = parse_pipe(root, lexer_list);
	while ((*lexer_list) != NULL
		&& ((*lexer_list)->token.type == TOKEN_AND
			|| (*lexer_list)->token.type == TOKEN_OR))
	{
		new_node = create_node((*lexer_list)->token);
		new_node->left = root;
		*lexer_list = (*lexer_list)->next;
		new_node->right = parse_pipe(root, lexer_list);
		root = new_node;
	}
	return (root);
}

t_ast_node	*parse_semi_colon(t_ast_node *root, t_lexer_node **lexer_list)
{
	t_ast_node	*new_node;

	if ((*lexer_list) == NULL)
		return (root);
	root = parse_and_or(root, lexer_list);
	while ((*lexer_list) != NULL
		&& (*lexer_list)->token.type == TOKEN_SEMICOLON)
	{
		new_node = create_node((*lexer_list)->token);
		new_node->left = root;
		*lexer_list = (*lexer_list)->next;
		new_node->right = parse_and_or(new_node->right, lexer_list);
		root = new_node;
	}
	return (root);
}
