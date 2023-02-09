/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_quote_content.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:42:36 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/09 15:42:47 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	skip_quote_content(char *str)
{
	size_t	i;
	char	start;

	start = *str;
	i = 0;
	if (start != '\'' && start != '"')
		return (i);
	i++;
	while (str[i] != start)
		i++;
	return (i++);
}
