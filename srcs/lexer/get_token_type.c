/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 17:22:24 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/08 17:22:49 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_types	get_token_type(t_lexer *lexer, size_t index)
{
	size_t	token_len;
	size_t	i;

	i = 0;
	while (lexer->tkn_types_array[i] != NULL)
	{
		token_len = ft_strlen(lexer->tkn_types_array[i]);
		if (ft_strncmp(&lexer->input[index],
				lexer->tkn_types_array[i], token_len) == 0)
			return ((t_token_types)i);
		i++;
	}
	if (lexer->input[index] != '\0')
		return (COMMAND);
	return (_EOF);
}
