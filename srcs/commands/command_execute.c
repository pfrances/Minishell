/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 17:09:48 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/07 16:27:23 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_input_files(t_cmd *cmd, t_input_output *input_output)
{
	if (input_output->type == FILE_INPUT)
		input_output->fd = open(input_output->filename, O_RDONLY);
	if (input_output->fd == -1)
		perror(input_output->filename);
	if (cmd->input_fd != STDIN_FILENO)
		close(cmd->input_fd);
	cmd->input_fd = input_output->fd;
}

void	open_output_files(t_cmd *cmd, t_input_output *input_output)
{
	if (input_output->type == FILE_OUTPUT)
		input_output->fd = open(input_output->filename,
				O_WRONLY | O_CREAT | O_TRUNC, 0664);
	else
		input_output->fd = open(input_output->filename,
				O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (input_output->fd == -1)
		perror(input_output->filename);
	if (cmd->output_fd != STDOUT_FILENO)
		close(cmd->output_fd);
	cmd->output_fd = input_output->fd;
}

void	set_up_input_output(t_cmd *cmd)
{
	size_t	i;

	i = 0;
	while (g_state.error_state == NO_ERROR && cmd->input_output[i] != NULL)
	{
		if (cmd->input_output[i]->type == STD_INPUT)
			set_here_doc(cmd, cmd->input_output[i]);
		else if (cmd->input_output[i]->type == FILE_INPUT)
			open_input_files(cmd, cmd->input_output[i]);
		else
			open_output_files(cmd, cmd->input_output[i]);
		i++;
	}
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

void	reset_redirection(t_cmd *cmd)
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

void	execute_command(t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	set_up_input_output(cmd);
	if (g_state.error_state != NO_ERROR)
		return ;
	pid = fork();
	if (pid == 0)
	{
		set_signal_handling();
		execve(cmd->path, cmd->args, cmd->envp);
		perror(cmd->path);
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		actualise_exit_status(WEXITSTATUS(status));
	}
	else
	{
		perror("fork failed");
		g_state.error_state = FORK_FAILED;
	}
	reset_redirection(cmd);
}
