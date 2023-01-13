/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:55:02 by pfrances          #+#    #+#             */
/*   Updated: 2023/01/13 13:03:22 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_syntax_tree(t_ast_node **node)
{
	if (node == NULL || *node == NULL)
		return ;
	free_syntax_tree(&(*node)->left);
	free_syntax_tree(&(*node)->right);
	free((*node)->token.lexem);
	(*node)->token.lexem = NULL;
	free(*node);
	*node = NULL;
}

t_ast_node	*create_node(t_token token)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (node == NULL)
		return (NULL);
	node->token = token;
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_ast_node	*parse_command(t_lexer *lexer)
{
	t_ast_node	*new_node;

	if (lexer->current_token_type == TOKEN_COMMAND)
	{
		new_node = create_node(lexer->current_token);
		if (get_next_token(lexer))
			return (new_node);
	}
	return (NULL);
}

t_ast_node	*parse_bracket(t_ast_node *root, t_lexer *lexer)
{
	t_ast_node	*new_node;

	if (lexer->current_token_type != TOKEN_EOF)
		root = parse_command(lexer);
	while (root != NULL
			&& (lexer->current_token_type == TOKEN_OPEN_BRACKET
			|| lexer->current_token_type == TOKEN_CLOSE_BRACKET))
	{
		new_node = create_node(lexer->current_token);
		if (new_node == NULL)
			return (NULL);
		new_node->left = root;
		if (get_next_token(lexer))
		{
			new_node->right = parse_semi_colon(root, lexer);
			if (new_node == NULL)
				return (NULL);
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
			return (NULL) ;
		new_node->left = root;
		if (get_next_token(lexer))
		{
			new_node->right = parse_bracket(root, lexer);
			if (new_node->right == NULL)
				return (NULL);
		}
		root = new_node;
	}
	return (root);
}

t_ast_node	*parse_pipe(t_ast_node *root, t_lexer *lexer)
{
	t_ast_node	*new_node;

	if (lexer->current_token_type != TOKEN_EOF)
		root = parse_input_output(root, lexer);
	while (root != NULL && lexer->current_token_type == TOKEN_PIPE)
	{
		new_node = create_node(lexer->current_token);
		if (new_node == NULL)
			return (NULL);
		new_node->left = root;
		if (get_next_token(lexer))
		{
			new_node->right = parse_input_output(root, lexer);
			if (new_node->right == NULL)
				return (NULL);
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
	while (root != NULL &&
		(lexer->current_token_type == TOKEN_AND
		|| lexer->current_token_type == TOKEN_OR))
	{
		new_node = create_node(lexer->current_token);
		if (new_node == NULL)
			return (NULL);
		new_node->left = root;
		if (get_next_token(lexer))
		{
			new_node->right = parse_pipe(root, lexer);
			if (new_node->right == NULL)
				return (NULL);
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
	while (lexer->current_token_type == TOKEN_SEMICOLON && root != NULL)
	{
		new_node = create_node(lexer->current_token);
		if (new_node == NULL)
			break ;
		new_node->left = root;
		if (get_next_token(lexer) && lexer->current_token_type != TOKEN_EOF)
		{
			new_node->right = parse_and_or(root, lexer);
			if (new_node->right == NULL)
				break ;
		}
		root = new_node;
	}
	return (root);
}

bool	init_lexer(t_lexer *lexer)
{
	lexer->tkn_types_array = ft_split_charset(TOKENS_CHARSET, SPACES_CHARSET);
	if (lexer->tkn_types_array == NULL)
		return (false);
	lexer->input = readline(" > ");
	if (lexer->input == NULL)
	{
		free_array((void **)lexer->tkn_types_array);
		return (false);
	}
	add_history(lexer->input);
	lexer->bracket_count = 0;
	lexer->index = 0;
	lexer->list_head = NULL;
	return (get_next_token(lexer));
}

t_ast_node	*parser_job()
{
	t_ast_node	*root;
	t_lexer		lexer;

	if (init_lexer(&lexer) == false)
		return (NULL);
	root = NULL;
	root = parse_semi_colon(root, &lexer);
	if (lexer.current_token_type == TOKEN_EOF)
	{
		print_syntax_tree(root);
		// free_lexer(&lexer);
		// free_syntax_tree(&root);
	}
	return (root);
}
