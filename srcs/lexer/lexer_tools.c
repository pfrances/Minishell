/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 19:07:00 by pfrances          #+#    #+#             */
/*   Updated: 2023/01/15 12:01:01 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	print_tokens(t_lexer_node *list)
{
	while (list != NULL)
	{
		ft_printf("%s", list->token.lexem);
		list = list->next;
		if (list != NULL)
			ft_printf("-->");
		else
			ft_printf("\n");
	}
}

char	*ft_strjoin_with_free(char *s1, char const *s2)
{
	char	*result;
	size_t	s1_len;
	size_t	s2_len;
	size_t	total_length;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	total_length = s1_len + s2_len;
	result = malloc(sizeof(char) * (total_length + 1));
	if (result == NULL)
		return (result);
	ft_strlcpy(result, s1, s1_len + 1);
	ft_strlcpy(result + s1_len, s2, s2_len + 1);
	free(s1);
	return (result);
}

bool	check_bracket(t_lexer *lexer)
{
	if (lexer->current_token_type == TOKEN_OPEN_BRACKET)
		lexer->bracket_count++;
	else if (lexer->current_token_type == TOKEN_CLOSE_BRACKET)
		lexer->bracket_count--;
	return (lexer->bracket_count >= 0);
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
		return (TOKEN_COMMAND);
	return (TOKEN_EOF);
}

bool	read_new_line(t_lexer *lexer)
{
	char	*input;

	input = readline(PROMPT_INDENT);
	if (input == NULL)
		return (false);
	add_history(input);
	lexer->input = ft_strjoin_with_free(lexer->input, input);
	if (lexer->input == NULL)
		return (false);
	return (true);
}
