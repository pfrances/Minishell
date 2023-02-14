/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin_type.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 20:11:19 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/14 15:22:43 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	has_option(char *arg1)
{
	size_t	i;

	if (arg1 == NULL)
		return (false);
	i = 0;
	if (arg1[i] == '-')
	{
		while (arg1[i] == '-')
			i++;
		if (arg1[i] != '\0' && ft_isspace(arg1[i]) != false)
			return (true);
	}
	return (false);
}

char	*set_name_to_lower(char *cmd)
{
	char	*name;
	size_t	i;

	name = ft_strdup(cmd);
	if (name == NULL)
		return (NULL);
	i = 0;
	while (name[i] != '\0')
	{
		name[i] = ft_tolower(name[i]);
		i++;
	}
	return (name);
}

t_builtin_type	get_builtin_type(char *name, char *arg1, size_t name_len)
{
	if (!ft_strncmp("echo", name, name_len + 1))
		return (_ECHO);
	else if (!ft_strncmp("cd", name, name_len + 1))
		return (CD);
	else if (!ft_strncmp("pwd", name, name_len + 1) && !has_option(arg1))
		return (PWD);
	else if (!ft_strncmp("export", name, name_len + 1) && !has_option(arg1))
		return (EXPORT);
	else if (!ft_strncmp("unset", name, name_len + 1) && !has_option(arg1))
		return (UNSET);
	else if (!ft_strncmp("env", name, name_len + 1) && arg1 == NULL)
		return (ENV);
	else if (!ft_strncmp("exit", name, name_len + 1) && !has_option(arg1))
		return (EXIT);
	else
		return (NOT_BUILTIN);
}

t_builtin_type	check_builtin_type(char **cmd_args)
{
	char			*name;
	size_t			name_len;
	t_builtin_type	type;

	if (cmd_args == NULL || cmd_args[0] == NULL)
		return (EMPTY_CMD);
	name = set_name_to_lower(cmd_args[0]);
	if (name == NULL)
	{
		g_state.error = MALLOC_FAILED;
		return (NOT_BUILTIN);
	}
	name_len = ft_strlen(name);
	type = get_builtin_type(name, cmd_args[1], name_len);
	free(name);
	return (type);
}
