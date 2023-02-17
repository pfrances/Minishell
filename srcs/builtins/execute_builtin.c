/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 19:31:39 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/17 16:42:49 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_builtin(t_cmd *cmd)
{
	if (cmd->cmd_type == EXIT)
		builtin_exit(cmd);
	else
		g_state.exit_status = 0;
	if (cmd->cmd_type == _ECHO)
		builtin_echo(cmd);
	else if (cmd->cmd_type == CD)
		builtin_cd(cmd);
	else if (cmd->cmd_type == PWD)
		builtin_pwd(cmd);
	else if (cmd->cmd_type == EXPORT)
		builtin_export(cmd);
	else if (cmd->cmd_type == UNSET)
		builtin_unset(cmd);
	else if (cmd->cmd_type == ENV)
		builtin_env(cmd);
	actualise_exit_status(g_state.exit_status);
}
