/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 22:34:37 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/09 20:51:10 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_init(t_lexer *lexer, t_ast_node **root, char *envp[])
{
	*root = NULL;
	g_state.exit_status_str = NULL;
	actualise_exit_status(0);
	g_state.stop_signal_flag = false;
	rl_done = 0;
	set_signal_handling();
	g_state.envp = dup_array(envp);
	if (g_state.envp == NULL)
		g_state.error_state = ALLOCATION_FAILED;
	lexer->tkn_types_array = ft_split_charset(TOKENS_CHARSET, SPACES_CHARSET);
	if (lexer->tkn_types_array == NULL)
		g_state.error_state = ALLOCATION_FAILED;
	lexer->list_head = NULL;
	lexer->input = NULL;
	if (g_state.error_state == ALLOCATION_FAILED)
	{
		free_all(lexer, *root);
		exit(EXIT_FAILURE);
	}
	g_state.error_state = NO_ERROR;
}
