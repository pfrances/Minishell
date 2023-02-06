/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 15:16:54 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/06 19:54:09 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_wildcards_token(char *lexem, size_t *start)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (lexem[i] != '\0')
	{
		i += skip_quote_content(&lexem[i]);
		if (lexem[i] == '*')
		{
			j = i;
			while (i > 0 && ft_isspace(lexem[i - 1]) == false
				&& lexem[i - 1] != '"' && lexem[i - 1] != '\'')
				i--;
			while (lexem[j + 1] != '\0' && ft_isspace(lexem[j + 1]) == false
				&& lexem[j + 1] != '"' && lexem[j + 1] != '\'')
				j++;
			*start = i;
			return (ft_strndup(&lexem[i], j - i + 1));
		}
		else
			i++;
	}
	return (NULL);
}

bool	match(char *token, char *filename)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (token[i] != '\0' && filename[j] != '\0')
	{
		if (token[i] == '*')
		{
			while (token[i] == '*')
				i++;
			if (token[i] == '\0')
				return (true);
			while (filename[j] != '\0' && filename[j] != token[i])
				j++;
		}
		else if (token[i] == filename[j])
		{
			i++;
			j++;
		}
		else
			return (false);
	}
	while (token[i] == '*')
		i++;
	return (token[i] == filename[j]);
}

char	*search_in_current_dir(char *token)
{
	DIR				*current_dir;
	struct dirent	*entry;
	char			*result;

	result = ft_calloc(1, sizeof(char));
	current_dir = opendir(".");
	if (current_dir == NULL)
	{
		perror("opendir");
		return (NULL);
	}
	entry = readdir(current_dir);
	while (entry != NULL && g_state.error_state == NO_ERROR)
	{
		if (match(token, entry->d_name))
			result = add_filename_to_result(result, entry);
		entry = readdir(current_dir);
	}
	if (closedir(current_dir) < 0)
	{
		free(result);
		perror("closedir");
		return (NULL);
	}
	return (result);
}

void	expend_wildcards(char **lexem)
{
	char	*token;
	char	*patern;
	size_t	start;
	size_t	i;

	token = get_wildcards_token(*lexem, &start);
	while (token != NULL)
	{
		patern = search_in_current_dir(token);
		if (patern == NULL)
		{
			g_state.error_state = ALLOCATION_FAILED;
			return ;
		}
		if (*patern != '\0')
			*lexem = update_lexem(*lexem, token, patern, start);
		i = start + ft_strlen(token);
		free(token);
		free(patern);
		token = get_wildcards_token(*lexem + i - 1, &start);
	}
}
