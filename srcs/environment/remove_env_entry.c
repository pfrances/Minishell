/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_env_entry.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 10:21:36 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/08 14:02:15 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_env_entry(char *var_name)
{
	size_t	i;
	size_t	j;
	char	**new_envp;

	new_envp = resize_array(g_state.envp, -1);
	if (new_envp == NULL)
		return ;
	i = 0;
	j = 0;
	while (g_state.envp[i] != NULL)
	{
		if (cmp_var_names(g_state.envp[i], var_name) == false)
		{
			new_envp[j] = g_state.envp[i];
			j++;
		}
		else
			free(g_state.envp[i]);
		i++;
	}
	new_envp[j] = NULL;
	free(g_state.envp);
	g_state.envp = new_envp;
}
