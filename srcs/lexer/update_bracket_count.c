/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_bracket_count.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 19:07:00 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/08 17:25:52 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_bracket_count(t_lexer *lexer)
{
	if (lexer->current_token_type == OPEN_BRACKET)
		lexer->bracket_count++;
	else if (lexer->current_token_type == CLOSE_BRACKET)
		lexer->bracket_count--;
}
