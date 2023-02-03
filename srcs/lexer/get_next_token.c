/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 19:04:23 by pfrances          #+#    #+#             */
/*   Updated: 2023/01/27 11:38:28 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	get_other_token(t_lexer *lexer)
{
	size_t	token_len;
	size_t	i;

	if (lexer->current_token_type == _EOF)
		return (add_node_to_list(lexer, 1));
	i = 0;
	while (lexer->tkn_types_array[i] != NULL)
	{
		token_len = ft_strlen(lexer->tkn_types_array[i]);
		if (ft_strncmp(&lexer->input[lexer->index],
				lexer->tkn_types_array[i], token_len) == 0)
		{
			update_bracket_count(lexer);
			return (add_node_to_list(lexer, token_len));
		}
		i++;
	}
	return (false);
}

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
			if (get_command_line_ending(lexer) == false)
				return (false);
		}
		else
			(*i)++;
	}
	return (true);
}

bool	get_command_token(t_lexer *lexer)
{
	size_t	i;

	i = 0;
	while (get_token_type(lexer, lexer->index + i) == COMMAND)
	{
		if (get_quotes_content(lexer, &i) == false)
			return (false);
		i++;
	}
	while (i > 0 && ft_isspace(lexer->input[lexer->index + i]))
		i--;
	if (check_redirection(lexer, &lexer->input[lexer->index], i) == false)
		return (false);
	return (add_node_to_list(lexer, i));
}

bool	check_endline(t_lexer *lexer)
{
	t_token_types	last_token;

	if (lexer->current_token_type != _EOF)
		return (true);
	last_token = lexer->current_node->token.type;
	if (lexer->bracket_count == 0)
	{
		if (last_token == SEMICOLON || last_token == COMMAND
			|| last_token == CLOSE_BRACKET)
			return (true);
	}
	while (lexer->current_token_type == _EOF)
	{
		if (get_command_line_ending(lexer) == false)
			return (false);
		lexer->current_token_type = get_token_type(lexer, lexer->index);
	}
	return (true);
}

bool	get_next_token(t_lexer *lexer)
{
	while (ft_isspace(lexer->input[lexer->index]))
		lexer->index++;
	lexer->current_token_type = get_token_type(lexer, lexer->index);
	if (check_endline(lexer) == false)
		return (false);
	if (lexer->current_token_type == COMMAND)
	{
		if (get_command_token(lexer) == false)
			return (false);
	}
	else
	{
		if (get_other_token(lexer) == false)
			return (false);
	}
	lexer->current_node = last_lexer_list(lexer->list_head);
	lexer->current_token = &lexer->current_node->token;
	return (true);
}
