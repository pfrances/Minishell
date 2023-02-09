/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 22:21:41 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/08 13:01:57 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_unset(t_cmd *cmd)
{
	size_t	i;

	if (g_state.error_state != NO_ERROR || cmd->args[0] == NULL)
		return ;
	i = 1;
	while (g_state.error_state == NO_ERROR && cmd->args[i] != NULL)
	{
		if (is_var_in_env(cmd->args[i]))
			remove_env_entry(cmd->args[i]);
		i++;
	}
}
