/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:22:54 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/04 17:29:41 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_to_create_full_path(char *path, char *name)
{
	char	*full_path;
	size_t	path_len;
	size_t	total_length;

	if (path == NULL || name == NULL)
		return (NULL);
	path_len = ft_strlen(path);
	total_length = path_len + ft_strlen(name) + 1;
	full_path = ft_calloc(total_length + 1, sizeof(char));
	if (full_path == NULL)
		return (NULL);
	ft_strlcpy(full_path, path, path_len + 1);
	full_path[path_len] = '/';
	ft_strlcat(full_path + path_len + 1, name, total_length + 1);
	return (full_path);
}

char	*get_cmd_path(char *name, char **env_paths)
{
	char	*path;
	size_t	i;

	if (name == NULL)
		return (NULL);
	if (access(name, X_OK) == 0)
		return (ft_strdup(name));
	i = 0;
	while (env_paths[i] != NULL && name[0] != '\0')
	{
		path = join_to_create_full_path(env_paths[i], name);
		if (path == NULL)
			return (NULL);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (ft_strdup(name));
}
