/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_var_in_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 12:59:55 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/08 14:21:44 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_var_in_env(char *var_name)
{
	size_t	i;

	i = 0;
	while (g_state.envp[i] != NULL)
	{
		if (cmp_var_names(g_state.envp[i], var_name) == true)
			return (true);
		i++;
	}
	return (false);
}
