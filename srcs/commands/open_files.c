/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 20:07:10 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/07 20:16:46 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_input_files(t_cmd *cmd, t_redirect *redirect)
{
	if (redirect->type == FILE_INPUT)
		redirect->fd = open(redirect->filename, O_RDONLY);
	if (redirect->fd == -1)
		perror(redirect->filename);
	if (cmd->input_fd != STDIN_FILENO)
		close(cmd->input_fd);
	cmd->input_fd = redirect->fd;
}

void	open_output_files(t_cmd *cmd, t_redirect *redirect)
{
	if (redirect->type == FILE_OUTPUT)
		redirect->fd = open(redirect->filename,
				O_WRONLY | O_CREAT | O_TRUNC, 0664);
	else
		redirect->fd = open(redirect->filename,
				O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (redirect->fd == -1)
		perror(redirect->filename);
	if (cmd->output_fd != STDOUT_FILENO)
		close(cmd->output_fd);
	cmd->output_fd = redirect->fd;
}
