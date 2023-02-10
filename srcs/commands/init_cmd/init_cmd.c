/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:46:41 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/10 11:10:42 by pfrances         ###   ########.fr       */
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

t_cmd	*init_cmd(char *lexem)
{
	t_cmd	*cmd;
	char	*expanded_lexem;

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
	if (g_state.error != NO_ERROR)
	{
		free_cmd(cmd);
		return (NULL);
	}
	return (cmd);
}
