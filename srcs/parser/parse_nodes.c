/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:11:49 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/07 12:01:53 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*parse_command(t_lexer *lexer)
{
	t_ast_node	*new_node;

	if (g_state.error_state == NO_ERROR && lexer->current_token_type == COMMAND)
	{
		new_node = create_node(lexer);
		if (g_state.error_state != NO_ERROR)
			return (NULL);
		if (get_next_token(lexer))
			return (new_node);
	}
	g_state.error_state = SYNTAX_ERROR;
	g_state.error_index = lexer->index - ft_strlen(lexer->current_token->lexem);
	return (NULL);
}

t_ast_node	*parse_bracket(t_ast_node *root, t_lexer *lexer)
{
	t_ast_node	*new_node;

	if (g_state.error_state == NO_ERROR
		&& lexer->current_token_type == OPEN_BRACKET)
	{
		if (get_next_token(lexer) == false)
			return (root);
		new_node = parse_semi_colon(root, lexer);
		if (lexer->current_token_type == CLOSE_BRACKET)
			get_next_token(lexer);
		return (new_node);
	}
	else if (g_state.error_state == NO_ERROR
		&& lexer->current_token_type != _EOF)
		root = parse_command(lexer);
	return (root);
}

t_ast_node	*parse_pipe(t_ast_node *root, t_lexer *lexer)
{
	t_ast_node	*new_node;

	if (g_state.error_state == NO_ERROR && lexer->current_token_type != _EOF)
		root = parse_bracket(root, lexer);
	while (g_state.error_state == NO_ERROR && lexer->current_token_type == PIPE)
	{
		new_node = create_node(lexer);
		if (g_state.error_state != NO_ERROR)
			return (root);
		new_node->left = root;
		root = new_node;
		if (get_next_token(lexer) && lexer->current_token_type != _EOF)
		{
			root->right = parse_bracket(root, lexer);
			if (g_state.error_state != NO_ERROR)
				return (root);
		}
	}
	return (root);
}

t_ast_node	*parse_and_or(t_ast_node *root, t_lexer *lexer)
{
	t_ast_node	*new_node;

	if (g_state.error_state == NO_ERROR && lexer->current_token_type != _EOF)
		root = parse_pipe(root, lexer);
	while (g_state.error_state == NO_ERROR
		&& (lexer->current_token_type == AND
			|| lexer->current_token_type == OR))
	{
		new_node = create_node(lexer);
		if (g_state.error_state != NO_ERROR)
			return (root);
		new_node->left = root;
		root = new_node;
		if (get_next_token(lexer))
		{
			root->right = parse_pipe(root, lexer);
			if (g_state.error_state != NO_ERROR)
				return (root);
		}
	}
	return (root);
}

t_ast_node	*parse_semi_colon(t_ast_node *root, t_lexer *lexer)
{
	t_ast_node	*new_node;

	if (g_state.error_state == NO_ERROR && lexer->current_token_type != _EOF)
		root = parse_and_or(root, lexer);
	while (g_state.error_state == NO_ERROR
		&& lexer->current_token_type == SEMICOLON)
	{
		new_node = create_node(lexer);
		if (g_state.error_state != NO_ERROR)
			return (root);
		new_node->left = root;
		root = new_node;
		if (get_next_token(lexer) && (lexer->current_token_type != _EOF
				&& lexer->current_token_type != CLOSE_BRACKET))
		{
			root->right = parse_and_or(root, lexer);
			if (g_state.error_state != NO_ERROR)
				return (root);
		}
	}
	return (root);
}
