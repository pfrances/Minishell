/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_nodes1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:11:49 by pfrances          #+#    #+#             */
/*   Updated: 2023/01/15 12:49:42 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast_node	*parse_command(t_lexer *lexer)
{
	t_ast_node	*new_node;

	if (lexer->current_token_type == TOKEN_COMMAND)
	{
		new_node = create_node(lexer->current_token);
		if (get_next_token(lexer))
			return (new_node);
		else
			return (free_syntax_tree(&new_node));
	}
	return (NULL);
}

t_ast_node	*parse_bracket(t_ast_node *root, t_lexer *lexer)
{
	t_ast_node	*new_node;

	if (lexer->current_token_type != TOKEN_EOF)
		root = parse_command(lexer);
	while (root == NULL
		&& (lexer->current_token_type == TOKEN_OPEN_BRACKET
			|| lexer->current_token_type == TOKEN_CLOSE_BRACKET))
	{
		new_node = create_node(lexer->current_token);
		if (new_node == NULL)
			return (free_syntax_tree(&root));
		new_node->left = root;
		if (get_next_token(lexer))
		{
			new_node->right = parse_semi_colon(root, lexer);
			if (new_node->right == NULL)
				return (free_syntax_tree(&new_node));
		}
		root = new_node;
	}
	return (root);
}

t_ast_node	*parse_input_output(t_ast_node *root, t_lexer *lexer)
{
	t_ast_node	*new_node;

	if (lexer->current_token_type != TOKEN_EOF)
		root = parse_bracket(root, lexer);
	while (root != NULL
		&& (lexer->current_token_type == TOKEN_INPUT
			|| lexer->current_token_type == TOKEN_OUTPUT
			|| lexer->current_token_type == TOKEN_OUTPUT_ADD))
	{
		new_node = create_node(lexer->current_token);
		if (new_node == NULL)
			return (free_syntax_tree(&root));
		new_node->left = root;
		if (get_next_token(lexer))
		{
			new_node->right = parse_bracket(root, lexer);
			if (new_node->right == NULL)
				return (free_syntax_tree(&new_node));
		}
		root = new_node;
	}
	return (root);
}
