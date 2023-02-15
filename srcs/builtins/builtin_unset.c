/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 22:21:41 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/15 23:18:25 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_unset(t_cmd *cmd)
{
	size_t	i;

	if (g_state.error != NO_ERROR || cmd->args[0] == NULL)
		return ;
	i = 1;
	while (g_state.error == NO_ERROR && cmd->args[i] != NULL)
	{
		if (is_valid_envp_name(cmd->args[i]) == false)
			print_envp_token_error_msg(cmd->args[i], "unset");
		else if (search_entry_in_env(cmd->args[i]) != NULL)
			remove_env_entry(cmd->args[i]);
		i++;
	}
	update_all_env();
}
