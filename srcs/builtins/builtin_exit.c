/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 20:18:43 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/17 16:55:39 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_exit_status(char *arg1)
{
	bool	valid_nbr;
	int		status;

	valid_nbr = false;
	status = (int)ft_atol_with_error_check(arg1, &valid_nbr);
	if (valid_nbr == true)
		return (status);
	else
	{
		ft_putstr_fd("exit: ", STDERR_FILENO);
		ft_putstr_fd(arg1, STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		return (2);
	}
}

void	builtin_exit(t_cmd *cmd)
{
	if (cmd->args[1] != NULL)
	{
		if (cmd->args[2] != NULL)
		{
			ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
			g_state.exit_status = 1;
			return ;
		}
		g_state.exit_status = get_exit_status(cmd->args[1]);
	}
	g_state.error = EXIT_CALL;
	reset_redirections(cmd);
	exit(g_state.exit_status);
}
