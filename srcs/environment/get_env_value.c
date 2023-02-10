/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 10:22:00 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/10 10:45:58 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			return (var_value);
		}
		free(var_name);
		free(var_value);
		i++;
	}
	return (NULL);
}
