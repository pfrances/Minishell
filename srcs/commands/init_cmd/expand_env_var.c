/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 21:05:34 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/17 17:15:21 by pfrances         ###   ########.fr       */
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
	if (lexem[i] != '$')
		return (NULL);
	i++;
	if (lexem[i] != '$' || lexem[i] != '?')
	{
		if (lexem[i] == '\0' || ft_isspace(lexem[i]) == true || lexem[i] == '='
			|| lexem[i] == '\'' || lexem[i] == '"')
			return (NULL);
		i++;
		while (lexem[i] != '\0' && lexem[i] != '$' && !ft_isspace(lexem[i])
			&& lexem[i] != '=' && lexem[i] != '\'' && lexem[i] != '"')
			i++;
	}
	else
		i++;
	name = ft_strndup(lexem, i);
	if (name == NULL)
		g_state.error = MALLOC_FAILED;
	return (name);
}

void	expend_single_var(char **value, char **name, char **lexem, size_t *i)
{
	if (*value == NULL && ((*name)[1] == '$' || (*name)[1] == '?'))
	{
		g_state.error = MALLOC_FAILED;
		free(*name);
		free(*lexem);
		*lexem = NULL;
		return ;
	}
	if (*value != NULL)
		*value = expand_env_var(*value);
	*lexem = update_cmd_lexem(*lexem, *name, *value, *i);
	if (*value != NULL)
		*i += ft_strlen(*value);
	free(*name);
	free(*value);
	if (*lexem == NULL)
		g_state.error = MALLOC_FAILED;
}

char	*get_apropriate_value(char *name)
{
	char	*value;

	if (name[1] == '?')
	{
		value = ft_strdup(g_state.exit_status_str);
		if (value == NULL)
			g_state.error = MALLOC_FAILED;
	}
	else if (name[1] == '$')
	{
		value = ft_strdup("`Unable to get PID`");
		if (value == NULL)
			g_state.error = MALLOC_FAILED;
	}
	else
		value = get_env_value(&name[1]);
	return (value);
}

char	*expand_env_var(char *lexem)
{
	size_t	i;
	char	*name;
	char	*value;
	bool	on_double_quotes;

	i = 0;
	on_double_quotes = false;
	while (g_state.error == NO_ERROR && lexem != NULL && lexem[i] != '\0')
	{
		if (lexem[i] == '\"')
			on_double_quotes = !on_double_quotes;
		if (lexem[i] == '\'' && on_double_quotes == false)
			i += skip_simple_quote(&lexem[i]);
		name = search_env_var(&lexem[i]);
		if (name != NULL)
		{
			value = get_apropriate_value(name);
			expend_single_var(&value, &name, &lexem, &i);
		}
		else if (lexem[i] != '\0')
			i++;
	}
	return (lexem);
}
