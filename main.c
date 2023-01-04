/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 12:32:19 by pfrances          #+#    #+#             */
/*   Updated: 2023/01/04 20:07:37 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lexer(t_lexer *lexer)
{
	free_array((void **)lexer->tkn_types_array);
	free_lexer_list(lexer->list);
	free(lexer->input);
}

int	main(int argc, char *argv[])
{
	t_lexer	lexer;

	(void)argv;
	if (argc == 1)
	{
		if (lexer_job(&lexer) == false)
			ft_printf("error\n");
		print_tokens(lexer.list);
		free_lexer(&lexer);
	}
	return (0);
}
