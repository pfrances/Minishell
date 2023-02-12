/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 10:22:00 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/12 12:04:52 by pfrances         ###   ########.fr       */
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
	size_t	i;
	char	*var_name;
	char	*var_value;

	i = 0;
	while (g_state.envp[i] != NULL)
	{
		if (split_env_var(g_state.envp[i], &var_name, &var_value) == false)
			return (NULL);
		if (cmp_var_names(g_state.envp[i], var_name_to_find) == true)
		{
			free(var_name);
			var_value = tokenise_env_value(var_value);
			if (var_value == NULL)
				g_state.error = MALLOC_FAILED;
			remove_quotes(var_value);
			return (var_value);
		}
		free(var_name);
		free(var_value);
		i++;
	}
	return (NULL);
}
