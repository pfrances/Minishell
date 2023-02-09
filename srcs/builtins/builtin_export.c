/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 22:20:34 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/08 14:17:18 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_without_arg(void)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (g_state.envp[i] != NULL)
	{
		j = 0;
		while (g_state.envp[i][j] != '=')
			j++;
		write(STDOUT_FILENO, g_state.envp[i], j - 1);
		write(STDOUT_FILENO, "=\"", 2);
		write(STDOUT_FILENO, &g_state.envp[i][j],
			ft_strlen(&g_state.envp[i][j]));
		write(STDOUT_FILENO, "\"\n", 2);
		i++;
	}
}

void	builtin_export(t_cmd *cmd)
{
	char	*var_name;
	char	*var_value;
	size_t	i;

	if (g_state.error_state != NO_ERROR || cmd->args[0] == NULL)
		return ;
	if (cmd->args[1] == NULL)
		export_without_arg();
	i = 1;
	while (g_state.error_state == NO_ERROR && cmd->args[i] != NULL)
	{
		if (split_env_var(cmd->args[i], &var_name, &var_value))
		{
			if (is_var_in_env(var_name) == true)
				update_env_entry(cmd->args[i], var_name);
			else
				add_entry_to_env(cmd->args[i]);
			free(var_name);
			free(var_value);
		}
		i++;
	}
}
