/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env_entry.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 10:21:57 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/08 12:42:03 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_entry_to_env(char *entry)
{
	size_t	i;
	char	**new_envp;

	new_envp = resize_array(g_state.envp, 1);
	if (new_envp == NULL)
		return ;
	i = 0;
	while (g_state.envp[i] != NULL)
	{
		new_envp[i] = g_state.envp[i];
		i++;
	}
	new_envp[i] = ft_strdup(entry);
	if (new_envp[i] == NULL)
		g_state.error_state = ALLOCATION_FAILED;
	new_envp[i + 1] = NULL;
	free(g_state.envp);
	g_state.envp = new_envp;
}
