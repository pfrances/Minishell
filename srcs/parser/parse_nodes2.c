/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_nodes2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:11:49 by pfrances          #+#    #+#             */
/*   Updated: 2023/01/15 12:16:54 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast_node	*parse_pipe(t_ast_node *root, t_lexer *lexer)
{
	t_ast_node	*new_node;

	if (lexer->current_token_type != TOKEN_EOF)
		root = parse_input_output(root, lexer);
	while (root && lexer->current_token_type == TOKEN_PIPE)
	{
		new_node = create_node(lexer->current_token);
		if (new_node == NULL)
			return (free_syntax_tree(&root));
		new_node->left = root;
		if (get_next_token(lexer) && lexer->current_token_type != TOKEN_EOF)
		{
			new_node->right = parse_input_output(root, lexer);
			if (new_node->right == NULL)
				return (free_syntax_tree(&new_node));
		}
		root = new_node;
	}
	return (root);
}

t_ast_node	*parse_and_or(t_ast_node *root, t_lexer *lexer)
{
	t_ast_node	*new_node;

	if (lexer->current_token_type != TOKEN_EOF)
		root = parse_pipe(root, lexer);
	while (root != NULL
		&& (lexer->current_token_type == TOKEN_AND
			|| lexer->current_token_type == TOKEN_OR))
	{
		new_node = create_node(lexer->current_token);
		if (new_node == NULL)
			return (free_syntax_tree(&root));
		new_node->left = root;
		if (get_next_token(lexer))
		{
			new_node->right = parse_pipe(root, lexer);
			if (new_node->right == NULL)
				return (free_syntax_tree(&new_node));
		}
		root = new_node;
	}
	return (root);
}

t_ast_node	*parse_semi_colon(t_ast_node *root, t_lexer *lexer)
{
	t_ast_node	*new_node;

	if (lexer->current_token_type != TOKEN_EOF)
		root = parse_and_or(root, lexer);
	while (root != NULL && lexer->current_token_type == TOKEN_SEMICOLON)
	{
		new_node = create_node(lexer->current_token);
		if (new_node == NULL)
			return (free_syntax_tree(&root));
		new_node->left = root;
		if (get_next_token(lexer) && lexer->current_token_type != TOKEN_EOF)
		{
			new_node->right = parse_and_or(root, lexer);
			if (new_node->right == NULL)
				return (free_syntax_tree(&new_node));
		}
		root = new_node;
	}
	return (root);
}
