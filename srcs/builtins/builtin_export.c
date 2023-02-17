/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 22:20:34 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/17 17:47:58 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp_entry	**init_entry_in_order_array(void)
{
	t_envp_entry	**entry_in_order;
	void			**ptr;
	size_t			i;

	ptr = resize_array((void **)g_state.envp_entries, 0);
	entry_in_order = (t_envp_entry **)ptr;
	if (entry_in_order == NULL)
		return (NULL);
	i = 0;
	while (g_state.envp_entries[i] != NULL)
	{
		entry_in_order[i] = g_state.envp_entries[i];
		i++;
	}
	entry_in_order[i] = NULL;
	return (entry_in_order);
}

void	sort_entry_array(t_envp_entry **array)
{
	t_envp_entry	*tmp_entry;
	size_t			array_size;
	size_t			i;
	size_t			j;

	array_size = array_len((void **)array);
	i = 0;
	while (i < array_size)
	{
		j = i + 1;
		while (j < array_size)
		{
			if (ft_strncmp(array[i]->name, array[j]->name,
					ft_strlen(array[i]->name) + 1) > 0)
			{
				tmp_entry = array[i];
				array[i] = array[j];
				array[j] = tmp_entry;
			}
			j++;
		}
		i++;
	}
}

t_envp_entry	**get_entry_in_order(void)
{
	t_envp_entry	**entry_in_order;

	entry_in_order = init_entry_in_order_array();
	if (entry_in_order == NULL)
		return (NULL);
	sort_entry_array(entry_in_order);
	return (entry_in_order);
}

void	export_without_arg(void)
{
	size_t			i;
	t_envp_entry	*entry;
	t_envp_entry	**entry_in_order;

	entry_in_order = get_entry_in_order();
	if (entry_in_order == NULL)
		return ;
	i = 0;
	while (entry_in_order[i] != NULL)
	{
		entry = entry_in_order[i];
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
	free(entry_in_order);
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
		{
			print_envp_token_error_msg(cmd->args[i], "export");
			g_state.exit_status = 1;
		}
		else
		{
			split_env_var(cmd->args[i], &var_name, &var_value);
			update_env_entry(var_name, var_value);
		}
		i++;
	}
	update_all_env();
}
