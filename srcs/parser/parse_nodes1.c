/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_nodes1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:11:49 by pfrances          #+#    #+#             */
/*   Updated: 2023/01/16 19:52:03 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast_node	*parse_command(t_lexer *lexer)
{
	t_ast_node	*new_node;

	if (!lexer->ast_error && lexer->current_token_type == TOKEN_COMMAND)
	{
		new_node = create_node(lexer);
		if (get_next_token(lexer))
			return (new_node);
	}
	lexer->ast_error = true;
	lexer->ast_syntax_error = true;
	return (NULL);
}

t_ast_node	*parse_bracket(t_ast_node *root, t_lexer *lexer)
{
	t_ast_node	*new_node;

	if (!lexer->ast_error && lexer->current_token_type == TOKEN_OPEN_BRACKET)
	{
		if (get_next_token(lexer) == false)
			return (root);
		new_node = parse_semi_colon(root, lexer);
		if (lexer->current_token_type == TOKEN_CLOSE_BRACKET
			&& get_next_token(lexer))
			return (new_node);
	}
	else if (!lexer->ast_error && lexer->current_token_type != TOKEN_EOF)
		root = parse_command(lexer);
	return (root);
}
