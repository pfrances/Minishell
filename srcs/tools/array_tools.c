/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 12:38:56 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/15 19:30:07 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	array_len(void **array)
{
	size_t	i;

	i = 0;
	while (array[i] != NULL)
		i++;
	return (i);
}

void	free_array(void **array)
{
	size_t	i;

	if (array == NULL)
		return ;
	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	**resize_array(void **array, int diff)
{
	void	**new_array;

	new_array = malloc(sizeof(void *) * (array_len((void **)array) + 1 + diff));
	if (new_array == NULL)
	{
		g_state.error = MALLOC_FAILED;
		return (NULL);
	}
	return (new_array);
}

char	**dup_array(char **array)
{
	size_t	i;
	char	**dup;

	dup = malloc(sizeof(char *) * (array_len((void **)array) + 1));
	if (dup == NULL)
	{
		g_state.error = MALLOC_FAILED;
		return (NULL);
	}
	i = 0;
	while (array[i] != NULL)
	{
		dup[i] = ft_strdup(array[i]);
		if (dup[i] == NULL)
		{
			while (i--)
				free(dup[i]);
			free(dup);
			g_state.error = MALLOC_FAILED;
			return (NULL);
		}
		i++;
	}
	dup[i] = NULL;
	return (dup);
}
