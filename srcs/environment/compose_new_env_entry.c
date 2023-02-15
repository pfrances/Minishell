/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compose_new_entry.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 21:25:22 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/15 21:25:25 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*compose_new_env_entry(char *env_name, char *env_value)
{
	char	*new_entry;

	if (env_name == NULL)
		return (NULL);
	if (env_value != NULL)
		new_entry = strjoin_with_sep(ft_strdup(env_name), env_value, "=");
	else
		new_entry = ft_strjoin(env_name, "=");
	if (new_entry == NULL)
		g_state.error = MALLOC_FAILED;
	return (new_entry);
}
