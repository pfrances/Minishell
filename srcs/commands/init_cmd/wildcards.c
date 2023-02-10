/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 15:16:54 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/10 10:36:46 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_filename_to_result(char *result, char *filename)
{
	if (*result == '\0')
		result = strjoin_with_sep(result, filename, "");
	else
		result = strjoin_with_sep(result, filename, " ");
	if (result == NULL)
	{
		g_state.error = MALLOC_FAILED;
		return (NULL);
	}
	return (result);
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
	while (entry != NULL && g_state.error == NO_ERROR)
	{
		if (wildcards_match(token, entry->d_name))
			result = add_filename_to_result(result, entry->d_name);
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
			g_state.error = MALLOC_FAILED;
			return ;
		}
		if (*patern != '\0')
		{
			*lexem = update_cmd_lexem(*lexem, token, patern, start);
			i = start + ft_strlen(patern);
		}
		else
			i = start + ft_strlen(token);
		free(token);
		free(patern);
		token = get_wildcards_token(*lexem + i, &start);
	}
}
