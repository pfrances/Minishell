/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 17:20:30 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/08 17:20:44 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*strjoin_with_sep(char *s1, char *s2, char *join)
{
	char	*result;
	size_t	s1_len;
	size_t	s2_len;
	size_t	join_len;
	size_t	total_length;

	if (s1 == NULL || s2 == NULL || join == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	join_len = ft_strlen(join);
	total_length = s1_len + s2_len + join_len;
	result = malloc(sizeof(char) * (total_length + 1));
	if (result == NULL)
		return (result);
	ft_strlcpy(result, s1, s1_len + 1);
	ft_strlcpy(result + s1_len, join, join_len + 1);
	ft_strlcpy(result + s1_len + join_len, s2, s2_len + 1);
	free(s1);
	return (result);
}
