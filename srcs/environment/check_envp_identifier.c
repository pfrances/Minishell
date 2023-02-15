/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_envp_identifier.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:39:29 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/15 23:18:59 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_envp_token_error_msg(char *entry, char *builtin_name)
{
	size_t	i;

	i = 0;
	while (entry[i] != '\0' && entry[i] != '=')
		i++;
	ft_putstr_fd(builtin_name, STDERR_FILENO);
	write(STDERR_FILENO, ": `", 3);
	write(STDERR_FILENO, entry, i);
	ft_putendl_fd(ENVP_UNVALID_TOKEN_MSG, STDERR_FILENO);
}

bool	is_valid_envp_name(char *name)
{
	size_t	i;

	i = 0;
	if (name[i] == '\0' || (ft_isalpha(name[i]) == false && name[i] != '_'))
		return (false);
	while (name[i] != '\0')
	{
		if (ft_isalnum(name[i]) == false && name[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

bool	is_valid_envp_identifier(char *entry)
{
	size_t	i;

	i = 0;
	if (entry[i] == '\0' || (ft_isalpha(entry[i]) == false && entry[i] != '_'))
		return (false);
	i++;
	while (entry[i] != '\0' && entry[i] != '=')
	{
		if (ft_isalnum(entry[i]) == false && entry[i] != '_')
			return (false);
		i++;
	}
	return (true);
}
