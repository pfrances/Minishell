/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 22:20:34 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/15 22:38:30 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_without_arg(void)
{
	size_t			i;
	t_envp_entry	*entry;

	i = 0;
	while (g_state.envp_entries[i] != NULL)
	{
		entry = g_state.envp_entries[i];
		write(STDOUT_FILENO, EXPORT_DECLARE_MSG, ft_strlen(EXPORT_DECLARE_MSG));
		write(STDOUT_FILENO, entry->name, ft_strlen(entry->name));
		if (entry->is_declared == true)
		{
			write(STDOUT_FILENO, "=\"", 2);
			write(STDOUT_FILENO, entry->value, ft_strlen(entry->value));
			write(STDOUT_FILENO, "\"", 1);
		}
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}

void	builtin_export(t_cmd *cmd)
{
	char	*var_name;
	char	*var_value;
	size_t	i;

	if (g_state.error != NO_ERROR || cmd->args[0] == NULL)
		return ;
	if (cmd->args[1] == NULL)
		export_without_arg();
	i = 1;
	while (g_state.error == NO_ERROR && cmd->args[i] != NULL)
	{
		if (is_valid_envp_identifier(cmd->args[i]) == false)
			print_envp_token_error_msg(cmd->args[i], "export");
		else
		{
			split_env_var(cmd->args[i], &var_name, &var_value);
			update_env_entry(var_name, var_value);
		}
		i++;
	}
	update_all_env();
}
