/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:31:43 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/15 23:36:11 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp_entry	*set_one_envp_entry(char *entry_str)
{
	t_envp_entry	*entry;

	entry = malloc(sizeof(t_envp_entry));
	if (entry == NULL)
		return (NULL);
	entry->entry = ft_strdup(entry_str);
	if (entry->entry == NULL)
	{
		free(entry);
		return (NULL);
	}
	entry->is_declared = true;
	split_env_var(entry_str, &entry->name, &entry->value);
	if (g_state.error == MALLOC_FAILED)
	{
		free(entry->entry);
		free(entry);
		return (NULL);
	}
	return (entry);
}

t_envp_entry	**set_envp_entry(char **envp)
{
	size_t			i;
	t_envp_entry	**entries;

	entries = malloc(sizeof(t_envp_entry *) * (array_len((void **)envp) + 1));
	if (entries == NULL)
		return (NULL);
	i = 0;
	while (envp[i] != NULL)
	{
		entries[i] = set_one_envp_entry(envp[i]);
		if (entries[i] == NULL)
		{
			g_state.error = MALLOC_FAILED;
			free_envp();
			return (NULL);
		}
		i++;
	}
	entries[i] = NULL;
	return (entries);
}

bool	set_up_envp(char **envp)
{
	g_state.envp_entries = NULL;
	g_state.envp = dup_array(envp);
	if (g_state.envp == NULL)
	{
		g_state.error = MALLOC_FAILED;
		return (false);
	}
	g_state.envp_entries = set_envp_entry(g_state.envp);
	if (g_state.envp_entries == NULL)
	{
		g_state.error = MALLOC_FAILED;
		return (false);
	}
	return (true);
}
