/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 12:35:57 by pfrances          #+#    #+#             */
/*   Updated: 2023/01/08 15:39:52 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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
		if (lexer->input[lexer->index] == '\0' && lexer->bracket_count > 0)
			if (read_new_line(lexer) == false)
				return (false);
	}
	return (true);
}
