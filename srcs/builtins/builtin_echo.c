/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 22:10:54 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/09 22:24:03 by pfrances         ###   ########.fr       */
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
		ft_printf("\n");
		return ;
	}
	i = skip_echo_option(cmd);
	if (i == 1)
		option = false;
	else
		option = true;
	while (cmd->args[i] != NULL)
	{
		ft_printf("%s", cmd->args[i]);
		i++;
		if (cmd->args[i] == NULL && option == false)
			ft_printf("\n");
		else if (cmd->args[i] != NULL)
			ft_printf(" ");
	}
}
