/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env_entry.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 10:21:57 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/17 17:59:05 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp_entry	*set_last_entry(char *name, char *value)
{
	t_envp_entry	*new_envp;

	new_envp = malloc(sizeof(t_envp_entry));
	if (new_envp == NULL)
	{
		free(new_envp);
		free_envp();
		g_state.error = MALLOC_FAILED;
		return (NULL);
	}
	new_envp->name = name;
	new_envp->value = value;
	if (new_envp->value != NULL)
	{
		new_envp->entry = compose_new_env_entry(name, value);
		new_envp->is_declared = true;
	}
	else
	{
		new_envp->entry = NULL;
		new_envp->is_declared = false;
	}
	return (new_envp);
}

void	add_entry_to_env(char *name, char *value)
{
	size_t			i;
	t_envp_entry	**new_envp;

	new_envp = (t_envp_entry **)resize_array((void **)g_state.envp_entries, 1);
	if (new_envp == NULL)
		return ;
	i = 0;
	while (g_state.envp_entries[i] != NULL)
	{
		new_envp[i] = g_state.envp_entries[i];
		i++;
	}
	new_envp[i] = set_last_entry(name, value);
	if (new_envp == NULL)
		return ;
	new_envp[i + 1] = NULL;
	free(g_state.envp_entries);
	g_state.envp_entries = new_envp;
}
