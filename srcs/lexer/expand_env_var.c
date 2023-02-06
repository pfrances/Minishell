/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 21:05:34 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/06 22:12:33 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	skip_simple_quote(char *lexem)
{
	size_t	i;

	i = 1;
	while (lexem[i] != '\0')
	{
		if (lexem[i] == '\'')
			return (i + 1);
		i++;
	}
	return (0);
}

char	*search_env_var(char *lexem)
{
	size_t	i;
	char	*name;

	i = 0;
	if (lexem[i] == '\0' || lexem[i] != '$')
		return (NULL);
	i++;
	if (lexem[i] == '\0' || lexem[i] == '$' || ft_isspace(lexem[i]))
		return (NULL);
	i++;
	while (lexem[i] != '\0' && lexem[i] != '$' && !ft_isspace(lexem[i]))
		i++;
	name = ft_strndup(lexem, i + 1);
	if (name == NULL)
	{
		g_state.error_state = ALLOCATION_FAILED;
		return (NULL);
	}
	return (name);
}

char	*expand_env_var(char *lexem)
{
	size_t	i;
	char	*name;
	char	*value;

	i = 0;
	while (g_state.error_state == NO_ERROR && lexem[i] != '\0')
	{
		if (lexem[i] == '\'')
			i += skip_simple_quote(&lexem[i]);
		name = search_env_var(&lexem[i]);
		if (name != NULL)
		{
			value = getenv(&name[1]);
			lexem = update_lexem(lexem, name, value, i);
			free(name);
			if (lexem == NULL)
			{
				g_state.error_state = ALLOCATION_FAILED;
				return (NULL);
			}
			if (value != NULL)
				i += ft_strlen(value);
		}
		else
			i++;
	}
	return (lexem);
}
