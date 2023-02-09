/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 19:15:36 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/07 19:46:05 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_cd(t_cmd *cmd)
{
	if (cmd->args[1] == NULL)
		return ;
	if (chdir(cmd->args[1]) != 0)
		perror(cmd->args[1]);
}
