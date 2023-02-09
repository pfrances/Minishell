/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp_var_names.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:01:19 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/08 14:21:50 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	cmp_var_names(char *entry, char *var_name)
{
	size_t	i;
	size_t	var_name_len;

	i = 0;
	while (entry[i] != '\0' && entry[i] != '=')
		i++;
	var_name_len = ft_strlen(var_name);
	if (var_name_len != i)
		return (false);
	if (ft_strncmp(entry, var_name, var_name_len) != 0)
		return (false);
	return (true);
}
