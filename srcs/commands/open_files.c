/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 20:07:10 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/14 14:21:26 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_input_files(t_cmd *cmd, t_redirect *redirect)
{
	int	errno;

	errno = 0;
	if (redirect->type == FILE_INPUT)
		redirect->fd = open(redirect->filename, O_RDONLY);
	if (redirect->fd == -1)
	{
		perror(redirect->filename);
		g_state.error = FILE_OPENING_FAILED;
		if (cmd->output_fd != STDOUT_FILENO)
			close(cmd->output_fd);
		actualise_exit_status(errno);
		return ;
	}
	if (cmd->input_fd != STDIN_FILENO)
		close(cmd->input_fd);
	cmd->input_fd = redirect->fd;
}

void	open_output_files(t_cmd *cmd, t_redirect *redirect)
{
	int	errno;

	errno = 0;
	if (redirect->type == FILE_OUTPUT)
		redirect->fd = open(redirect->filename,
				O_WRONLY | O_CREAT | O_TRUNC, 0664);
	else
		redirect->fd = open(redirect->filename,
				O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (redirect->fd == -1)
	{
		perror(redirect->filename);
		g_state.error = FILE_OPENING_FAILED;
		if (cmd->input_fd != STDIN_FILENO)
			close(cmd->input_fd);
		actualise_exit_status(errno);
		return ;
	}
	if (cmd->output_fd != STDOUT_FILENO)
		close(cmd->output_fd);
	cmd->output_fd = redirect->fd;
}

void	open_redir_files(t_cmd *cmd)
{
	size_t	i;

	i = 0;
	while (g_state.error == NO_ERROR && cmd->redirect[i] != NULL)
	{
		if (cmd->redirect[i]->type == STD_INPUT)
			set_here_doc(cmd, cmd->redirect[i]);
		else if (cmd->redirect[i]->type == FILE_INPUT)
			open_input_files(cmd, cmd->redirect[i]);
		else
			open_output_files(cmd, cmd->redirect[i]);
		i++;
	}
}
