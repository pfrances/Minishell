/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_all_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 19:58:52 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/19 16:38:07 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	allocate_envp_ptr(void)
{
	size_t	i;
	size_t	ptr_count;

	i = 0;
	ptr_count = 0;
	while (g_state.envp_entries[i] != NULL)
	{
		if (g_state.envp_entries[i]->value != NULL)
		{
			g_state.envp_entries[i]->is_declared = true;
			ptr_count++;
		}
		i++;
	}
	free_array((void **)g_state.envp);
	g_state.envp = malloc(sizeof(char *) * (ptr_count + 1));
	if (g_state.envp == NULL)
	{
		g_state.error = MALLOC_FAILED;
		free_envp();
		return (false);
	}
	return (true);
}

void	update_all_env(void)
{
	size_t	i;
	size_t	j;

	if (allocate_envp_ptr() == false)
		return ;
	i = 0;
	j = 0;
	while (g_state.envp_entries[i] != NULL)
	{
		if (g_state.envp_entries[i]->is_declared == true)
		{
			g_state.envp[j] = ft_strdup(g_state.envp_entries[i]->entry);
			if (g_state.envp[j] == NULL)
			{
				g_state.error = MALLOC_FAILED;
				free_envp();
				return ;
			}
			j++;
		}
		i++;
	}
	g_state.envp[j] = NULL;
}
