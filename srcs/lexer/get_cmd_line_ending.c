/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_line_ending.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 17:24:54 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/10 10:36:46 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	update_last_command(t_lexer *lexer)
{
	t_token	*last_token;
	size_t	i;
	char	*old_lexem;
	char	*lexem_ending;

	if (lexer->current_node == NULL)
		return (true);
	lexer->index++;
	last_token = &lexer->current_node->token;
	if (last_token->type != COMMAND
		|| get_token_type(lexer, lexer->index) != COMMAND)
		return (true);
	i = 0;
	while (get_token_type(lexer, lexer->index + i) == COMMAND)
		i++;
	lexem_ending = ft_strndup(&lexer->input[lexer->index], i);
	old_lexem = last_token->lexem;
	last_token->lexem = strjoin_with_sep(old_lexem, lexem_ending, "\n");
	lexer->index += i;
	free(lexem_ending);
	if (last_token->lexem == NULL)
		return (false);
	return (true);
}

bool	get_cmd_line_ending(t_lexer *lexer)
{
	char	*input;

	g_state.current_phase = WAITING_CMD_LINE_END;
	input = readline(PROMPT_INDENT);
	if (g_state.stop_signal_flag == true || input == NULL)
	{
		free(input);
		if (g_state.stop_signal_flag == true)
			g_state.error = CMD_STOP;
		else
			g_state.error = PROGRAM_STOP;
		return (false);
	}
	if (lexer->current_token_type == COMMAND)
		lexer->input = strjoin_with_sep(lexer->input, input, "\n");
	else
		lexer->input = strjoin_with_sep(lexer->input, input, " ");
	free(input);
	if (lexer->input == NULL || update_last_command(lexer) == false)
	{
		g_state.error = MALLOC_FAILED;
		return (false);
	}
	return (true);
}
