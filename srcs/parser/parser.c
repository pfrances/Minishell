/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:55:02 by pfrances          #+#    #+#             */
/*   Updated: 2023/01/16 12:01:03 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast_node	*free_syntax_tree(t_ast_node **node)
{
	if (node == NULL || *node == NULL)
		return (NULL);
	free_syntax_tree(&(*node)->left);
	free_syntax_tree(&(*node)->right);
	free(*node);
	*node = NULL;
	return (NULL);
}

t_ast_node	*create_node(t_token token)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (node == NULL)
		return (NULL);
	node->token = token;
	node->left = NULL;
	node->right = NULL;
	return (node);
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
	if (get_next_token(lexer) == false)
	{
		free_lexer(lexer);
		return (false);
	}
	return (true);
}

t_ast_node	*parser_job(t_lexer *lexer)
{
	t_ast_node	*root;

	if (init_lexer(lexer) == false)
		return (NULL);
	root = NULL;
	root = parse_semi_colon(root, lexer);
	if (lexer->current_token_type == TOKEN_EOF)
		print_syntax_tree(root);
	else
	{
		print_error_msg(lexer);
		free_syntax_tree(&root);
		free_lexer(lexer);
		return (NULL);
	}
	return (root);
}
