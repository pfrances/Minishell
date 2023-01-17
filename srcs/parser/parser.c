/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:55:02 by pfrances          #+#    #+#             */
/*   Updated: 2023/01/17 11:18:26 by pfrances         ###   ########.fr       */
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

t_ast_node	*create_node(t_lexer *lexer)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (node == NULL)
	{
		lexer->error.type = ALLOCATION_FAILED;
		return (NULL);
	}
	node->token = lexer->current_token;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

bool	init_lexer(t_lexer *lexer)
{
	lexer->tkn_types_array = ft_split_charset(TOKENS_CHARSET, SPACES_CHARSET);
	if (lexer->tkn_types_array == NULL)
		return (false);
	lexer->input = readline("Minishell > ");
	if (lexer->input == NULL)
	{
		free_array((void **)lexer->tkn_types_array);
		return (false);
	}
	lexer->bracket_count = 0;
	lexer->index = 0;
	lexer->list_head = NULL;
	lexer->error.type = NONE;
	lexer->error.index = 0;
	if (get_next_token(lexer) == false)
	{
		free_lexer(lexer);
		return (false);
	}
	return (true);
}

bool	check_ast_error(t_lexer *lexer, t_ast_node *root)
{
	if (lexer->current_token_type != TOKEN_EOF)
	{
		lexer->error.type = SYNTAX_ERROR;
		lexer->error.index = lexer->index;
		lexer->error.index -= ft_strlen(lexer->current_token->lexem);
	}
	if (lexer->error.type == NONE)
		return (true);
	else
	{
		print_error_msg(lexer);
		if (lexer->error.type == ALLOCATION_FAILED)
		{
			free_syntax_tree(&root);
			free_lexer(lexer);
			clear_history();
		}
		return (false);
	}
}

t_ast_node	*parser_job(t_lexer *lexer)
{
	t_ast_node	*root;

	if (init_lexer(lexer) == false)
		return (NULL);
	root = NULL;
	root = parse_semi_colon(root, lexer);
	add_history(lexer->input);
	if (check_ast_error(lexer, root))
		print_syntax_tree(root);
	if (lexer->error.type == ALLOCATION_FAILED)
		return (NULL);
	return (root);
}
