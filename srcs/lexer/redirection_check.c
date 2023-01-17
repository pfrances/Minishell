/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:53:00 by pfrances          #+#    #+#             */
/*   Updated: 2023/01/16 23:41:50 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	print_redirection_error_msg(char *command, size_t index)
{
	ft_putstr_fd(ERROR_SYNTAX_MSG, STDERR_FILENO);
	write(STDERR_FILENO, &command[index], 1);
	if (command[index] == '\0')
		write(STDERR_FILENO, "newline", ft_strlen("newline"));
	else if (command[index] == command[index + 1])
		write(STDERR_FILENO, &command[index + 1], 1);
	write(STDERR_FILENO, "\n", 1);
}

bool	is_redirection_token(char *command, size_t *index)
{
	if (command[*index] == '>' || command[*index] == '<')
	{
		if (command[(*index) + 1] == command[*index])
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

size_t	skip_quote_content(char *str)
{
	size_t	i;
	char	start;

	start = *str;
	i = 0;
	if (start != '\'' && start != '"')
		return (i);
	i++;
	while (str[i] != start)
		i++;
	return (i++);
}

bool	check_redirection(t_lexer *lexer, char *command, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (is_redirection_token(command, &i))
		{
			while (i < len && ft_isspace(command[i]))
				i++;
			if (is_valid_starting_filename(command[i]) == false)
			{
				lexer->error.type = SYNTAX_ERROR;
				lexer->error.index = lexer->index + i;
				return (false);
			}
		}
		i += skip_quote_content(&command[i]);
		i++;
	}
	return (true);
}
