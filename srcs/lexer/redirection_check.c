/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:53:00 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/09 15:42:06 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_redirection_error_msg(char *cmd, size_t index)
{
	ft_putstr_fd(ERROR_SYNTAX_MSG, STDERR_FILENO);
	write(STDERR_FILENO, &cmd[index], 1);
	if (cmd[index] == '\0')
		write(STDERR_FILENO, "newline", ft_strlen("newline"));
	else if (cmd[index] == cmd[index + 1])
		write(STDERR_FILENO, &cmd[index + 1], 1);
	write(STDERR_FILENO, "\n", 1);
}

bool	is_redirection_token(char *cmd, size_t *index)
{
	if (cmd[*index] == '>' || cmd[*index] == '<')
	{
		if (cmd[(*index) + 1] == cmd[*index])
		{
			*index += 2;
			return (true);
		}
		*index += 1;
		return (true);
	}
	return (false);
}

bool	is_valid_starting_filename(char filename_start)
{
	if (filename_start == ';'
		|| filename_start == '&'
		|| filename_start == '|'
		|| filename_start == '>'
		|| filename_start == '<'
		|| filename_start == '!'
		|| filename_start == '-'
		|| filename_start == '('
		|| filename_start == ')'
		|| filename_start == '\0')
		return (false);
	return (true);
}

bool	check_redirection(t_lexer *lexer, char *cmd, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (is_redirection_token(cmd, &i))
		{
			while (i < len && ft_isspace(cmd[i]))
				i++;
			if (is_valid_starting_filename(cmd[i]) == false)
			{
				g_state.error_state = SYNTAX_ERROR;
				g_state.error_index = lexer->index + i;
				return (false);
			}
		}
		i += skip_quote_content(&cmd[i]);
		i++;
	}
	return (true);
}
