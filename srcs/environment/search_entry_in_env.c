/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_entry_in_env.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 23:19:58 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/15 23:21:31 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp_entry	*search_entry_in_env(char *var_name)
{
	size_t			i;
	size_t			var_name_len;
	t_envp_entry	*entry;

	if (var_name == NULL)
		return (NULL);
	var_name_len = ft_strlen(var_name);
	i = 0;
	while (g_state.envp_entries[i] != NULL)
	{
		entry = g_state.envp_entries[i];
		if (ft_strncmp(entry->name, var_name, var_name_len + 1) == 0)
			return (entry);
		i++;
	}
	return (NULL);
}
