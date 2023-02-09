/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:00:52 by pfrances          #+#    #+#             */
/*   Updated: 2023/01/26 19:01:35 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	count_ptr(char *input, const char *charset)
{
	size_t	ptr_count;
	size_t	i;

	i = 0;
	while (input[i] != '\0' && ft_strchr(charset, input[i]) != NULL)
		i++;
	ptr_count = 0;
	while (input[i] != '\0')
	{
		if (ft_strchr(charset, input[i]) == NULL)
		{
			while (input[i] != '\0' && ft_strchr(charset, input[i]) == NULL)
				i++;
			ptr_count++;
		}
		else
		{
			while (input[i] != '\0' && ft_strchr(charset, input[i]) != NULL)
				i++;
		}
	}
	return (ptr_count);
}

static size_t	fill_ptr_and_jump(char *input, char **dst, const char *charset)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (ft_strchr(charset, input[i]) != NULL)
		i++;
	j = 0;
	while (ft_strchr(charset, input[i + j]) == NULL)
		j++;
	*dst = ft_strndup(&input[i], j);
	if (*dst == NULL)
		return (0);
	return (i + j);
}

char	**ft_split_charset(char *input, const char *charset)
{
	char	**result;
	size_t	ptr_count;
	size_t	i;
	size_t	j;

	ptr_count = count_ptr(input, charset);
	result = malloc(sizeof(char *) * (ptr_count + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (i < ptr_count)
	{
		j += fill_ptr_and_jump(&input[j], &result[i], charset);
		if (result[i] == NULL)
		{
			while (i--)
				free(result[i]);
			free(result);
			return (NULL);
		}
		i++;
	}
	result[i] = NULL;
	return (result);
}
