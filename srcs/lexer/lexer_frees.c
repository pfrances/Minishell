/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_frees.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:33:44 by pfrances          #+#    #+#             */
/*   Updated: 2023/01/07 16:23:05 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	free_array(void **array)
{
	size_t	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_lexer_list(t_lexer_node *list)
{
	t_lexer_node	*trv;

	while (list != NULL)
	{
		trv = list->next;
		free(list->token.lexem);
		free(list);
		list = trv;
	}
}

void	free_lexer(t_lexer *lexer)
{
	free_array((void **)lexer->tkn_types_array);
	free_lexer_list(lexer->list);
	free(lexer->input);
}
