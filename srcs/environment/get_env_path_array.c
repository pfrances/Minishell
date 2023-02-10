/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_path_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 10:53:00 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/10 10:51:59 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_env_path_array(void)
{
	char	**path_array;
	char	*all_path_in_one_line;

	all_path_in_one_line = get_env_value("PATH");
	if (all_path_in_one_line == NULL)
		return (NULL);
	path_array = ft_split(all_path_in_one_line, ':');
	if (path_array == NULL)
		g_state.error = MALLOC_FAILED;
	free(all_path_in_one_line);
	return (path_array);
}
