/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:33:44 by pfrances          #+#    #+#             */
/*   Updated: 2022/12/31 13:09:41 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	free_lexer_list(t_lexer_list *list)
{
	t_lexer_list	*trv;

	while (list != NULL)
	{
		trv = list->next;
		free(list->token.content);
		free(list);
		list = trv;
	}
}
