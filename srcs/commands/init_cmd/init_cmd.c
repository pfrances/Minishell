/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:46:41 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/15 13:31:48 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_lexem(char *lexem)
{
	char	*expanded_lexem;

	expanded_lexem = ft_strdup(lexem);
	if (expanded_lexem == NULL)
	{
		g_state.error = MALLOC_FAILED;
		return (NULL);
	}
	expanded_lexem = expand_env_var(expanded_lexem);
	if (expanded_lexem != NULL)
		expend_wildcards(&expanded_lexem);
	return (expanded_lexem);
}

void	set_up_cmd_struct(t_cmd *cmd, char *lexem)
{
	char	**env_paths;

	set_input_output_args(cmd, lexem);
	if (g_state.error != NO_ERROR)
		return ;
	cmd->input_fd = STDIN_FILENO;
	cmd->input_fd_save = -1;
	cmd->output_fd = STDOUT_FILENO;
	cmd->output_fd_save = -1;
	cmd->builtin_type = check_builtin_type(cmd->args);
	if (cmd->builtin_type == NOT_BUILTIN)
	{
		env_paths = get_env_path_array();
		cmd->path = get_cmd_path(cmd->args[0], env_paths);
		free_array((void **)env_paths);
	}
	else
		cmd->path = NULL;
}

t_cmd	*parse_cmd(char *lexem)
{
	char	*expanded_lexem;
	t_cmd	*cmd;

	expanded_lexem = expand_lexem(lexem);
	if (expanded_lexem == NULL)
		return (NULL);
	cmd = allocate_cmd(expanded_lexem);
	if (cmd == NULL)
	{
		free(expanded_lexem);
		return (NULL);
	}
	set_up_cmd_struct(cmd, expanded_lexem);
	free(expanded_lexem);
	if (g_state.error == NO_ERROR)
		return (cmd);
	else
	{
		free_cmd(cmd);
		return (NULL);
	}
}

bool	init_cmd(t_ast_node *node)
{
	node->cmd = parse_cmd(node->token->lexem);
	if (node->cmd == NULL)
		return (false);
	open_redir_files(node->cmd);
	if (g_state.error == NO_ERROR)
		return (true);
	free_cmd(node->cmd);
	node->cmd = NULL;
	if (g_state.error == FILE_OPENING_FAILED)
		g_state.error = NO_ERROR;
	return (false);
}
