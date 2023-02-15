/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_env_var.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 10:24:36 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/08 10:25:17 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_env_var(char *var, char **var_name, char **var_value)
{
	size_t	i;

	if (ft_strchr(var, '=') == NULL)
	{
		*var_name = ft_strdup(var);
		*var_value = NULL;
		return ;
	}
	i = 0;
	while (var[i] != '=')
		i++;
	*var_name = ft_strndup(var, i);
	*var_value = ft_strdup(var + i + 1);
	if (*var_name == NULL || *var_value == NULL)
	{
		g_state.error = MALLOC_FAILED;
		free(*var_name);
		free(*var_value);
		*var_name = NULL;
		*var_value = NULL;
		return ;
	}
	return ;
}
