/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:55:02 by pfrances          #+#    #+#             */
/*   Updated: 2023/01/11 19:40:53 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_syntax_tree(t_ast_node *node)
{
	if (node == NULL)
		return ;
	free_syntax_tree(node->left);
	free_syntax_tree(node->right);
	free(node);
	node = NULL;
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

t_ast_node	*parse_semi_colon(t_ast_node *root, t_lexer *lexer)
{
	t_ast_node	*new_node;

	if (lexer->current_token_type != TOKEN_EOF)
		root = parse_command(lexer);
	while (lexer->current_token_type == TOKEN_SEMICOLON && root != NULL)
	{
		new_node = create_node(lexer->current_token);
		if (new_node == NULL)
			break ;
		new_node->left = root;
		if (get_next_token(lexer))
		{
			new_node->right = parse_command(lexer);
			if (new_node->right == NULL)
				break ;
		}
		root = new_node;
	}
	if (lexer->current_token_type != TOKEN_EOF)
	{
		free_lexer(lexer);
		free_syntax_tree(root);
		return (NULL);
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
	print_syntax_tree(root);
	free_lexer(&lexer);
	free_syntax_tree(root);
	return (root);
}
