/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 20:18:43 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/10 10:36:13 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_exit(t_cmd *cmd)
{
	if (cmd->args[1] != NULL)
		g_state.exit_status = ft_atoi(cmd->args[1]);
	g_state.error = EXIT_CALL;
	exit(g_state.error);
}
