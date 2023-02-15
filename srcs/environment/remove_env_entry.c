/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_env_entry.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 10:21:36 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/15 23:23:18 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_one_entry(t_envp_entry *entry)
{
	free(entry->name);
	free(entry->value);
	free(entry->entry);
	free(entry);
}

void	remove_env_entry(char *name)
{
	size_t			i;
	size_t			j;
	t_envp_entry	**new_envp;
	t_envp_entry	*entry;

	new_envp = (t_envp_entry **)resize_array((void **)g_state.envp_entries, -1);
	if (new_envp == NULL)
		return ;
	i = 0;
	j = 0;
	while (g_state.envp_entries[i] != NULL)
	{
		entry = g_state.envp_entries[i];
		if (ft_strncmp(entry->name, name, ft_strlen(name) + 1) != 0)
		{
			new_envp[j] = entry;
			j++;
		}
		else
			free_one_entry(entry);
		i++;
	}
	new_envp[j] = NULL;
	free(g_state.envp_entries);
	g_state.envp_entries = new_envp;
}
