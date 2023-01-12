/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_nodes1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:11:49 by pfrances          #+#    #+#             */
/*   Updated: 2023/01/11 12:42:47 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

t_ast_node	*parse_command(t_lexer_node **lexer_list)
{
	t_ast_node		*new_node;

	if (*lexer_list != NULL
		&& (*lexer_list)->token.type == TOKEN_COMMAND)
	{
		new_node = create_node((*lexer_list)->token);
		*lexer_list = (*lexer_list)->next;
		return (new_node);
	}
	else
		return (NULL);
}

t_ast_node	*parse_bracket(t_ast_node *root, t_lexer_node **lexer_list)
{
	t_ast_node	*new_node;

	if (*lexer_list != NULL)
		root = parse_command(lexer_list);
	while (*lexer_list != NULL && root != NULL
		&& ((*lexer_list)->token.type == TOKEN_OPEN_BRACKET
			|| (*lexer_list)->token.type == TOKEN_CLOSE_BRACKET))
	{
		new_node = create_node((*lexer_list)->token);
		if (new_node == NULL)
			return (NULL);
		new_node->left = root;
		*lexer_list = (*lexer_list)->next;
		if (*lexer_list != NULL)
		{
			new_node->right = parse_semi_colon(root, lexer_list);
			if (new_node == NULL)
				return (NULL);
		}
		root = new_node;
	}
	return (root);
}

t_ast_node	*parse_input_output(t_ast_node *root, t_lexer_node **lexer_list)
{
	t_ast_node	*new_node;

	if (*lexer_list != NULL)
		root = parse_bracket(root, lexer_list);
	while (*lexer_list != NULL && root != NULL
		&& ((*lexer_list)->token.type == TOKEN_INPUT
			|| (*lexer_list)->token.type == TOKEN_OUTPUT))
	{
		new_node = create_node((*lexer_list)->token);
		if (new_node == NULL)
			return (NULL);
		new_node->left = root;
		*lexer_list = (*lexer_list)->next;
		if (*lexer_list != NULL)
		{
			new_node->right = parse_bracket(root, lexer_list);
			if (new_node == NULL)
				return (NULL);
		}
		root = new_node;
	}
	return (root);
}
