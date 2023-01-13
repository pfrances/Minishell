/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 19:04:23 by pfrances          #+#    #+#             */
/*   Updated: 2023/01/13 13:19:47 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

bool	get_quotes_content(t_lexer *lexer, size_t *i)
{
	char	start;

	start = lexer->input[lexer->index + *i];
	if (start != '\"' && start != '\'')
		return (true);
	(*i)++;
	while (lexer->input[lexer->index + *i] != start)
	{
		if (lexer->input[lexer->index + *i] == '\0')
		{
			if (read_new_line(lexer) == false)
				return (false);
		}
		else
			(*i)++;
	}
	(*i)++;
	return (true);
}

bool	command_tokens_paterns(t_lexer *lexer)
{
	size_t	i;

	i = 0;
	while (get_token_type(lexer, lexer->index + i) == TOKEN_COMMAND)
	{
		if (get_quotes_content(lexer, &i) == false)
			return (false);
		i++;
	}
	return (add_node_to_list(lexer, i));
}

bool	check_bracket(t_lexer *lexer)
{
	if (lexer->current_token_type == TOKEN_OPEN_BRACKET)
		lexer->bracket_count++;
	else if (lexer->current_token_type == TOKEN_CLOSE_BRACKET)
		lexer->bracket_count--;
	return (lexer->bracket_count >= 0);
}

bool	other_tokens_patterns(t_lexer *lexer)
{
	size_t	token_len;
	size_t	i;

	if (lexer->current_token_type == TOKEN_EOF)
		return (add_node_to_list(lexer, 1));
	i = 0;
	while (lexer->tkn_types_array[i] != NULL)
	{
		token_len = ft_strlen(lexer->tkn_types_array[i]);
		if (ft_strncmp(&lexer->input[lexer->index],
				lexer->tkn_types_array[i], token_len) == 0)
		{
			if (check_bracket(lexer) == false)
				return (false);
			return (add_node_to_list(lexer, token_len));
		}
		i++;
	}
	return (false);
}

bool	get_next_token(t_lexer *lexer)
{
	while (ft_isspace(lexer->input[lexer->index]))
		lexer->index++;
	lexer->current_token_type = get_token_type(lexer, lexer->index);
	while (lexer->current_token_type == TOKEN_EOF)
	{
		lexer->current_token_type = get_token_type(lexer, lexer->index);
		if (read_new_line(lexer) == false)
			return (false);
	}
	if (lexer->current_token_type == TOKEN_COMMAND)
	{
		if (command_tokens_paterns(lexer) == false)
			return (false);
	}
	else
	{
		if (other_tokens_patterns(lexer) == false)
			return (false);
	}
	lexer->current_node = last_lexer_list(lexer->list_head);
	lexer->current_token = lexer->current_node->token;
	return (true);
}
