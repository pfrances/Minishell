/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:42:36 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/10 23:47:39 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*put_in_double_quotes(char *str)
{
	char	*result;
	size_t	total_len;

	total_len = ft_strlen(str) + 2;
	result = malloc(sizeof(char) * (total_len + 1));
	if (result == NULL)
		g_state.error = MALLOC_FAILED;
	else
	{
		result[0] = '"';
		ft_strlcpy(&result[1], str, total_len);
		result[total_len - 1] = '"';
		result[total_len] = '\0';
	}
	free(str);
	return (result);
}

void	remove_quotes(char *cmd_token)
{
	size_t	i;
	size_t	j;
	size_t	token_len;

	token_len = ft_strlen(cmd_token);
	i = 0;
	while (cmd_token[i] != '\0')
	{
		if (cmd_token[i] == '\'' || cmd_token[i] == '"')
		{
			j = i + 1;
			while (cmd_token[j] != cmd_token[i])
				j++;
			ft_memmove(&cmd_token[i], &cmd_token[i + 1], token_len - i);
			cmd_token[--token_len] = '\0';
			ft_memmove(&cmd_token[j - 1], &cmd_token[j], token_len - j);
			cmd_token[--token_len] = '\0';
			i = j - 1;
		}
		else
			i++;
	}
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
