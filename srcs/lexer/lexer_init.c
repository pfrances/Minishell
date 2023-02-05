/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:18:01 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/04 10:03:50 by pfrances         ###   ########.fr       */
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
		if (lexer->input == NULL || ft_strncmp(lexer->input, "exit", 5) == 0)
		{
			g_state.error_state = PROGRAM_STOP;
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

bool	init_lexer(t_lexer *lexer, char *envp[])
{
	lexer->list_head = NULL;
	lexer->all_path = NULL;
	lexer->input = NULL;
	lexer->tkn_types_array = ft_split_charset(TOKENS_CHARSET, SPACES_CHARSET);
	if (lexer->tkn_types_array == NULL)
		return (false);
	if (read_first_line(lexer) == false)
		return (false);
	lexer->bracket_count = 0;
	g_state.error_state = NO_ERROR;
	g_state.error_index = 0;
	lexer->current_node = NULL;
	lexer->envp = envp;
	lexer->all_path = ft_split(getenv("PATH"), ':');
	if (!lexer->envp || !lexer->all_path)
	{
		g_state.error_state = ALLOCATION_FAILED;
		return (false);
	}
	if (get_next_token(lexer) == false)
	{
		add_history(lexer->input);
		return (false);
	}
	return (true);
}
