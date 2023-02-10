/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:16:22 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/10 10:36:13 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_here_doc_pipe(t_cmd *cmd, char *here_doc_input)
{
	int		fd[2];

	if (pipe(fd) < 0)
		perror("pipe failed");
	else
	{
		cmd->input_fd = fd[0];
		write(fd[1], here_doc_input, ft_strlen(here_doc_input));
		write(fd[1], "\n", 1);
		close(fd[1]);
	}
}

void	set_here_doc(t_cmd *cmd, t_redirect *redirect)
{
	char	*here_doc_input;
	char	*new_line;

	here_doc_input = ft_calloc(1, sizeof(char));
	while (g_state.error == NO_ERROR)
	{
		new_line = readline("here_doc > ");
		if (new_line == NULL)
			g_state.error = CMD_STOP;
		else if (ft_strncmp(new_line, redirect->filename,
				ft_strlen(new_line) + 1) == 0)
			break ;
		else if (here_doc_input[0] == '\0')
			here_doc_input = strjoin_with_sep(here_doc_input, new_line, "");
		else
			here_doc_input = strjoin_with_sep(here_doc_input, new_line, "\n");
		free(new_line);
	}
	if (cmd->input_fd != STDIN_FILENO)
		set_here_doc_pipe(cmd, here_doc_input);
	free(here_doc_input);
	free(new_line);
}
