/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 10:22:00 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/15 21:17:20 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*tokenise_env_value(char *value)
{
	char	**splited_value;
	char	*result;
	size_t	i;

	splited_value = ft_split_charset(value, SPACES_CHARSET);
	free(value);
	if (splited_value == NULL)
		return (NULL);
	result = ft_calloc(1, 1);
	if (result != NULL)
	{
		i = 0;
		while (splited_value[i] != NULL)
		{
			expend_wildcards(&splited_value[i]);
			splited_value[i] = put_in_double_quotes(splited_value[i]);
			result = strjoin_with_sep(result, splited_value[i], " ");
			if (result == NULL)
				break ;
			i++;
		}
	}
	free_array((void **)splited_value);
	return (result);
}

char	*get_env_value(char *var_name_to_find)
{
	t_envp_entry	*entry;
	char			*value;

	entry = search_entry_in_env(var_name_to_find);
	if (entry == NULL || entry->is_declared == false)
		return (NULL);
	value = ft_strdup(entry->value);
	if (value == NULL)
	{
		g_state.error = MALLOC_FAILED;
		return (NULL);
	}
	value = tokenise_env_value(value);
	remove_quotes(value);
	return (value);
}
