/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:16:22 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/14 14:04:00 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_here_doc_pipe(t_cmd *cmd, char *here_doc_input)
{
	int	fd[2];

	if (g_state.error != NO_ERROR)
		return ;
	if (pipe(fd) < 0)
		perror("pipe failed");
	else
	{
		if (cmd->input_fd != STDIN_FILENO)
			close(cmd->input_fd);
		cmd->input_fd = fd[0];
		write(fd[1], here_doc_input, ft_strlen(here_doc_input));
		if (here_doc_input[0] != '\0')
			write(fd[1], "\n", 1);
		close(fd[1]);
	}
}

char	*get_here_doc_input(t_redirect *redirect)
{
	char	*here_doc_input;
	char	*new_line;

	here_doc_input = ft_calloc(1, sizeof(char));
	while (g_state.error == NO_ERROR)
	{
		new_line = readline("here_doc > ");
		if (new_line == NULL || g_state.stop_signal_flag == true)
		{
			if (new_line == NULL)
				write(STDOUT_FILENO, "\n", 1);
			free(here_doc_input);
			free(new_line);
			g_state.error = CMD_STOP;
			g_state.stop_signal_flag = false;
			return (NULL);
		}
		else if (ft_strncmp(new_line, redirect->filename,
				ft_strlen(new_line) + 1) == 0)
			break ;
		here_doc_input = strjoin_with_sep(here_doc_input, new_line, "\n");
		free(new_line);
	}
	free(new_line);
	return (here_doc_input);
}

void	set_here_doc(t_cmd *cmd, t_redirect *redirect)
{
	char	*here_doc_input;

	g_state.current_phase = HERE_DOC;
	here_doc_input = get_here_doc_input(redirect);
	if (here_doc_input != NULL)
	{
		set_here_doc_pipe(cmd, here_doc_input);
		free(here_doc_input);
	}
	g_state.current_phase = EXECUTING_CMD;
}
