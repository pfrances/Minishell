/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 22:34:37 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/15 17:31:31 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_lexer *lexer, t_ast_node **root, char *envp[])
{
	g_state.error = NO_ERROR;
	g_state.stop_signal_flag = false;
	g_state.exit_status_str = NULL;
	if (set_up_envp(envp) == false)
		return ;
	rl_done = 0;
	set_signal_handling();
	actualise_exit_status(0);
	*root = NULL;
	lexer->list_head = NULL;
	lexer->input = NULL;
	lexer->tkn_types_array = ft_split_charset(TOKENS_CHARSET, SPACES_CHARSET);
	if (lexer->tkn_types_array == NULL)
		g_state.error = MALLOC_FAILED;
	if (g_state.error != NO_ERROR)
	{
		free_all(lexer, *root);
		exit(EXIT_FAILURE);
	}
}
