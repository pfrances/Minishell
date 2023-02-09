/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 19:31:39 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/09 22:20:25 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_builtin(t_cmd *cmd)
{
	set_redirections(cmd);
	if (cmd->builtin_type == _ECHO)
		builtin_echo(cmd);
	else if (cmd->builtin_type == CD)
		builtin_cd(cmd);
	else if (cmd->builtin_type == PWD)
		builtin_pwd(cmd);
	else if (cmd->builtin_type == EXPORT)
		builtin_export(cmd);
	else if (cmd->builtin_type == UNSET)
		builtin_unset(cmd);
	else if (cmd->builtin_type == ENV)
		builtin_env(cmd);
	else if (cmd->builtin_type == EXIT)
		builtin_exit(cmd);
	reset_redirections(cmd);
}
