/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_reset_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 17:30:22 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/14 14:11:59 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_redirections(t_cmd *cmd)
{
	if (cmd->input_fd != STDIN_FILENO)
	{
		cmd->input_fd_save = dup(STDIN_FILENO);
		dup2(cmd->input_fd, STDIN_FILENO);
		close(cmd->input_fd);
	}
	if (cmd->output_fd != STDOUT_FILENO)
	{
		cmd->output_fd_save = dup(STDOUT_FILENO);
		dup2(cmd->output_fd, STDOUT_FILENO);
		close(cmd->output_fd);
	}
}

void	reset_redirections(t_cmd *cmd)
{
	if (cmd->input_fd_save != -1)
	{
		dup2(cmd->input_fd_save, STDIN_FILENO);
		close(cmd->input_fd_save);
	}
	if (cmd->output_fd_save != -1)
	{
		dup2(cmd->output_fd_save, STDOUT_FILENO);
		close(cmd->output_fd_save);
	}
}
