/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 12:32:19 by pfrances          #+#    #+#             */
/*   Updated: 2023/01/07 16:15:16 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"

int	main(int argc, char *argv[])
{
	t_lexer	lexer;

	(void)argv;
	if (argc == 1)
	{
		if (lexer_job(&lexer) == false)
			ft_printf("lexer error\n");
		print_tokens(lexer.list);
		if (parse(lexer.list) == false)
			ft_printf("parser error\n");
		free_lexer(&lexer);
	}
	return (0);
}
