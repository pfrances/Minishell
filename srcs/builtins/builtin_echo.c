/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 22:10:54 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/10 11:29:14 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	skip_echo_option(t_cmd *cmd)
{
	size_t	i;
	size_t	j;

	i = 1;
	while (cmd->args[i] != NULL)
	{
		j = 0;
		if (cmd->args[i][j] == '-' && cmd->args[i][j + 1] == 'n')
			j += 2;
		else
			return (i);
		while (cmd->args[i][j] != '\0')
		{
			if (cmd->args[i][j] != 'n')
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

void	builtin_echo(t_cmd *cmd)
{
	size_t	i;
	bool	option;

	if (cmd->args[1] == NULL)
	{
		write(STDOUT_FILENO, "\n", 1);
		return ;
	}
	i = skip_echo_option(cmd);
	if (i == 1)
		option = false;
	else
		option = true;
	while (cmd->args[i] != NULL)
	{
		write(STDOUT_FILENO, cmd->args[i], ft_strlen(cmd->args[i]));
		i++;
		if (cmd->args[i] == NULL && option == false)
			write(STDOUT_FILENO, "\n", 1);
		else if (cmd->args[i] != NULL)
			write(STDOUT_FILENO, " ", 1);
	}
}
