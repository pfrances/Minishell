/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env_entry.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 10:22:05 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/15 23:14:16 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_env_entry(char *name, char *value)
{
	t_envp_entry	*env_entry;

	env_entry = search_entry_in_env(name);
	if (env_entry == NULL)
		add_entry_to_env(name, value);
	else if (value != NULL)
	{
		free(env_entry->value);
		env_entry->value = value;
		env_entry->is_declared = true;
		free(env_entry->entry);
		env_entry->entry = compose_new_env_entry(name, value);
		free(name);
	}
	else
		free(name);
}
