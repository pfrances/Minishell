/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 20:18:43 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/16 22:04:59 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_exit(t_cmd *cmd)
{
	bool	valid_nbr;
	int		status;

	if (cmd->args[1] != NULL)
	{
		if (cmd->args[2] != NULL)
		{
			ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
			return ;
		}
		valid_nbr = false;
		status = (int)ft_atol_with_error_check(cmd->args[1], &valid_nbr);
		if (valid_nbr == true)
			g_state.exit_status = status;
		else
		{
			ft_putstr_fd("exit: ", STDERR_FILENO);
			ft_putstr_fd(cmd->args[1], STDERR_FILENO);
			ft_putendl_fd(": numeric argument required", STDERR_FILENO);
			g_state.exit_status = 2;
		}
	}
	g_state.error = EXIT_CALL;
	reset_redirections(cmd);
	exit(g_state.exit_status);
}
