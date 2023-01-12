/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 12:35:57 by pfrances          #+#    #+#             */
/*   Updated: 2023/01/11 12:29:54 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

bool	check_last_token(t_lexer_node *tail)
{
	t_token_types	token;

	if (tail == NULL)
		return (false);
	token = tail->token.type;
	if (token != TOKEN_COMMAND)
	{
		if (token == TOKEN_SEMICOLON || token == TOKEN_CLOSE_BRACKET)
			return (check_last_token(tail->prev));
		else
			return (false);
	}
	return (true);
}

bool	check_missing_token(t_lexer *lexer)
{
	if (lexer->bracket_count > 0)
		return (false);
	if (check_last_token(last_lexer_list(lexer->list)) == false)
		return (false);
	return (true);
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
	lexer->list = NULL;
	return (true);
}

bool	lexer_job(t_lexer *lexer)
{
	if (init_lexer(lexer) == false)
		return (false);
	while (lexer->input[lexer->index] != '\0')
	{
		if (ft_isspace(lexer->input[lexer->index]))
			lexer->index++;
		else if (manage_tokens(lexer) == false)
			return (false);
		if (lexer->input[lexer->index] == '\0' && !check_missing_token(lexer))
			if (read_new_line(lexer) == false)
				return (false);
	}
	return (true);
}
