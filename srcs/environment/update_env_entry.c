/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env_entry.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 10:22:05 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/08 14:21:06 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_env_entry(char *entry, char *var_name)
{
	size_t	i;

	i = 0;
	while (g_state.envp[i] != NULL)
	{
		if (cmp_var_names(g_state.envp[i], var_name) == true)
		{
			free(g_state.envp[i]);
			g_state.envp[i] = ft_strdup(entry);
			if (g_state.envp[i] == NULL)
				g_state.error_state = ALLOCATION_FAILED;
			return ;
		}
		i++;
	}
}
