/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_path_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 10:53:00 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/08 11:11:37 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_env_path_array(void)
{
	char	**path_array;
	char	*all_path_in_one_line;

	all_path_in_one_line = get_env_value("PATH");
	if (all_path_in_one_line == NULL)
	{
		if (g_state.error_state == NO_ERROR)
			g_state.error_state = ENV_ERROR;
		return (NULL);
	}
	path_array = ft_split(all_path_in_one_line, ':');
	if (path_array == NULL)
		g_state.error_state = ALLOCATION_FAILED;
	free(all_path_in_one_line);
	return (path_array);
}
