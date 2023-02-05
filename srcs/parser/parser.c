/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:55:02 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/04 10:16:28 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*parser_job(t_lexer *lexer, char *envp[])
{
	t_ast_node	*root;

	root = NULL;
	g_state.stop_signal_flag = false;
	rl_done = 0;
	if (init_lexer(lexer, envp) == false)
		return (NULL);
	root = parse_semi_colon(root, lexer);
	add_history(lexer->input);
	if (lexer->current_token_type != _EOF)
	{
		g_state.error_state = SYNTAX_ERROR;
		g_state.error_index = lexer->index;
		g_state.error_index -= ft_strlen(lexer->current_token->lexem);
	}
	if (g_state.error_state == NO_ERROR)
		g_state.current_phase = EXECUTING_CMD;
	return (root);
}
