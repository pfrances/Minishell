/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_match.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 19:29:11 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/09 16:16:18 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	skip_wildcard_content(char *token, char *filename)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (token[i] != '\0' && token[i] != '*')
		i++;
	j = 0;
	if (token[i] == '\0')
		i++;
	while (filename[j] != '\0' && ft_strncmp(&filename[j], token, i) != 0)
		j++;
	return (j);
}

bool	wildcards_match(char *token, char *filename)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (token[i] != '\0' && (filename[j] != '\0' || token[i] == '*'))
	{
		if (token[i] == '*')
		{
			while (token[i] == '*')
				i++;
			if (token[i] == '\0')
				return (true);
			j += skip_wildcard_content(&token[i], &filename[j]);
		}
		else if (token[i] == filename[j])
		{
			i++;
			j++;
		}
		else
			return (false);
	}
	return (token[i] == filename[j]);
}
