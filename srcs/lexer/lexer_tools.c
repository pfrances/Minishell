/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 19:07:00 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/05 16:22:29 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_bracket_count(t_lexer *lexer)
{
	if (lexer->current_token_type == OPEN_BRACKET)
		lexer->bracket_count++;
	else if (lexer->current_token_type == CLOSE_BRACKET)
		lexer->bracket_count--;
}

t_token_types	get_token_type(t_lexer *lexer, size_t index)
{
	size_t	token_len;
	size_t	i;

	i = 0;
	while (lexer->tkn_types_array[i] != NULL)
	{
		token_len = ft_strlen(lexer->tkn_types_array[i]);
		if (ft_strncmp(&lexer->input[index],
				lexer->tkn_types_array[i], token_len) == 0)
			return ((t_token_types)i);
		i++;
	}
	if (lexer->input[index] != '\0')
		return (COMMAND);
	return (_EOF);
}

char	*strjoin_with_sep(char *s1, char *s2, char *join)
{
	char	*result;
	size_t	s1_len;
	size_t	s2_len;
	size_t	join_len;
	size_t	total_length;

	if (s1 == NULL || s2 == NULL || join == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	join_len = ft_strlen(join);
	total_length = s1_len + s2_len + join_len;
	result = malloc(sizeof(char) * (total_length + 1));
	if (result == NULL)
		return (result);
	ft_strlcpy(result, s1, s1_len + 1);
	ft_strlcpy(result + s1_len, join, join_len + 1);
	ft_strlcpy(result + s1_len + join_len, s2, s2_len + 1);
	free(s1);
	return (result);
}

bool	update_last_command(t_lexer *lexer)
{
	t_token	*last_token;
	size_t	i;
	char	*old_lexem;
	char	*lexem_ending;

	if (lexer->current_node == NULL)
		return (true);
	lexer->index++;
	last_token = &lexer->current_node->token;
	if (last_token->type != COMMAND
		|| get_token_type(lexer, lexer->index) != COMMAND)
		return (true);
	i = 0;
	while (get_token_type(lexer, lexer->index + i) == COMMAND)
		i++;
	lexem_ending = ft_strndup(&lexer->input[lexer->index], i);
	old_lexem = last_token->lexem;
	last_token->lexem = strjoin_with_sep(old_lexem, lexem_ending, "\n");
	lexer->index += i;
	free(lexem_ending);
	if (last_token->lexem == NULL)
		return (false);
	return (true);
}

bool	get_command_line_ending(t_lexer *lexer)
{
	char	*input;

	g_state.current_phase = WAITING_CMD_LINE_END;
	input = readline(PROMPT_INDENT);
	if (g_state.stop_signal_flag == true || input == NULL
		|| ft_strncmp(input, "exit", 5) == 0)
	{
		free(input);
		if (g_state.stop_signal_flag == true)
			g_state.error_state = CMD_STOP;
		else
			g_state.error_state = PROGRAM_STOP;
		return (false);
	}
	if (lexer->current_token_type == COMMAND)
		lexer->input = strjoin_with_sep(lexer->input, input, "\n");
	else
		lexer->input = strjoin_with_sep(lexer->input, input, " ");
	free(input);
	if (lexer->input == NULL || update_last_command(lexer) == false)
	{
		g_state.error_state = ALLOCATION_FAILED;
		return (false);
	}
	return (true);
}
