/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:18:01 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/10 10:36:13 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	read_first_line(t_lexer *lexer)
{
	g_state.current_phase = WAITING_CMD_LINE;
	lexer->input = readline(PROMPT_MINISHELL);
	while (1)
	{
		lexer->index = 0;
		if (lexer->input == NULL)
		{
			g_state.error = PROGRAM_STOP;
			return (false);
		}
		while (ft_isspace(lexer->input[lexer->index]) == true)
			lexer->index++;
		if (g_state.stop_signal_flag)
			g_state.stop_signal_flag = false;
		else if (lexer->input[lexer->index] == '\0')
		{
			free(lexer->input);
			lexer->input = readline(PROMPT_MINISHELL);
		}
		else
			return (true);
	}
}

bool	init_lexer(t_lexer *lexer)
{
	lexer->list_head = NULL;
	lexer->input = NULL;
	if (read_first_line(lexer) == false)
		return (false);
	lexer->bracket_count = 0;
	lexer->current_node = NULL;
	if (get_next_token(lexer) == false)
	{
		add_history(lexer->input);
		return (false);
	}
	return (true);
}
