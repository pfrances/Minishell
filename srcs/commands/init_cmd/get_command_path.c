/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:22:54 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/17 16:07:09 by pfrances         ###   ########.fr       */
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

bool	check_permission(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) < 0)
	{
		perror("stat");
		return (false);
	}
	if (S_ISREG(path_stat.st_mode))
	{
		if (access(path, X_OK) == 0)
			return (true);
	}
	ft_putstr_fd(path, STDERR_FILENO);
	if (S_ISDIR(path_stat.st_mode))
		ft_putendl_fd(": Is a directory", STDERR_FILENO);
	else if (S_ISLNK(path_stat.st_mode))
		ft_putendl_fd(": Is a symbolic link", STDERR_FILENO);
	else
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
	actualise_exit_status(126);
	return (false);
}

bool	is_a_path(char *name)
{
	size_t	i;

	i = 0;
	while (name[i] != '\0')
	{
		if (name[i] == '/')
			return (true);
		i++;
	}
	return (false);
}

char	*search_path_from_env_path(char *name, char **env_paths)
{
	size_t	i;
	char	*path;

	i = 0;
	while (env_paths[i] != NULL && name[0] != '\0')
	{
		path = join_to_create_full_path(env_paths[i], name);
		if (path == NULL)
		{
			g_state.error = MALLOC_FAILED;
			return (NULL);
		}
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
	actualise_exit_status(127);
	return (NULL);
}

char	*get_cmd_path(char *name, char **env_paths)
{
	if (name == NULL)
		return (NULL);
	if (env_paths == NULL || is_a_path(name) == true)
	{
		if (access(name, F_OK) == 0)
		{
			if (check_permission(name) == true)
				return (ft_strdup(name));
			else
				return (NULL);
		}
		perror(name);
		actualise_exit_status(127);
	}
	else
		return (search_path_from_env_path(name, env_paths));
	return (NULL);
}
