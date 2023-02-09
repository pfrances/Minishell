/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actualise_exit_status.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 20:54:12 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/09 20:54:35 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	actualise_exit_status(int status)
{
	g_state.exit_status = status;
	free(g_state.exit_status_str);
	g_state.exit_status_str = ft_itoa(status);
	if (g_state.exit_status_str == NULL)
		g_state.error_state = ALLOCATION_FAILED;
}
