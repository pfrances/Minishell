/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_nodes2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:11:49 by pfrances          #+#    #+#             */
/*   Updated: 2023/01/16 09:46:48 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast_node	*parse_pipe(t_ast_node *root, t_lexer *lexer)
{
	t_ast_node	*new_node;

	if (lexer->current_token_type != TOKEN_EOF)
		root = parse_bracket(root, lexer);
	while (root != NULL && lexer->current_token_type == TOKEN_PIPE)
	{
		new_node = create_node(lexer->current_token);
		if (new_node == NULL)
			return (root);
		new_node->left = root;
		root = new_node;
		if (get_next_token(lexer) && lexer->current_token_type != TOKEN_EOF)
		{
			root->right = parse_bracket(root, lexer);
			if (root->right == NULL)
				return (root);
		}
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
			return (root);
		new_node->left = root;
		root = new_node;
		if (get_next_token(lexer))
		{
			root->right = parse_pipe(root, lexer);
			if (root->right == NULL)
				return (root);
		}
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
			return (root);
		new_node->left = root;
		root = new_node;
		if (get_next_token(lexer) && lexer->current_token_type != TOKEN_EOF)
		{
			root->right = parse_and_or(root, lexer);
			if (root->right == NULL)
				return (root);
		}
	}
	return (root);
}
