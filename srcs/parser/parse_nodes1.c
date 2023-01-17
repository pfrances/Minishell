/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_nodes1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:11:49 by pfrances          #+#    #+#             */
/*   Updated: 2023/01/17 10:51:22 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast_node	*parse_command(t_lexer *lexer)
{
	t_ast_node	*new_node;

	if (!lexer->error.type && lexer->current_token_type == TOKEN_COMMAND)
	{
		new_node = create_node(lexer);
		if (get_next_token(lexer))
			return (new_node);
	}
	lexer->error.type = SYNTAX_ERROR;
	lexer->error.index = lexer->index - ft_strlen(lexer->current_token->lexem);
	return (NULL);
}

t_ast_node	*parse_bracket(t_ast_node *root, t_lexer *lexer)
{
	t_ast_node	*new_node;

	if (!lexer->error.type && lexer->current_token_type == TOKEN_OPEN_BRACKET)
	{
		if (get_next_token(lexer) == false)
			return (root);
		new_node = parse_semi_colon(root, lexer);
		if (lexer->current_token_type == TOKEN_CLOSE_BRACKET)
			get_next_token(lexer);
		return (new_node);
	}
	else if (!lexer->error.type && lexer->current_token_type != TOKEN_EOF)
		root = parse_command(lexer);
	return (root);
}
