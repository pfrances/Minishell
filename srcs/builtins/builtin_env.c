/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 22:14:18 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/07 23:46:06 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_env(t_cmd *cmd)
{
	size_t	i;

	i = 0;
	(void)cmd;
	while (g_state.envp[i] != NULL)
	{
		ft_putendl_fd(g_state.envp[i], STDOUT_FILENO);
		i++;
	}
}
