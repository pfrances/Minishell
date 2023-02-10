/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:55:02 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/10 10:36:13 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*parser_job(t_lexer *lexer)
{
	t_ast_node	*root;

	root = NULL;
	g_state.stop_signal_flag = false;
	g_state.error = NO_ERROR;
	g_state.error_index = 0;
	rl_done = 0;
	if (init_lexer(lexer) == false)
		return (NULL);
	root = parse_semi_colon(root, lexer);
	add_history(lexer->input);
	if (g_state.error == NO_ERROR && lexer->current_token_type != _EOF)
	{
		g_state.error = SYNTAX_ERROR;
		g_state.error_index = lexer->index;
		g_state.error_index -= ft_strlen(lexer->current_token->lexem);
	}
	if (g_state.error == NO_ERROR)
		g_state.current_phase = EXECUTING_CMD;
	return (root);
}
