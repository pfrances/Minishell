/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 12:32:19 by pfrances          #+#    #+#             */
/*   Updated: 2023/01/11 12:38:38 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"

int	print_error_msg(char *error_msg, int exit_status)
{
	write(STDERR_FILENO, error_msg, ft_strlen(error_msg));
	return (exit_status);
}

int	main(int argc, char *argv[])
{
	t_lexer	lexer;

	(void)argv;
	if (argc == 1)
	{
		if (lexer_job(&lexer) == false)
		{
			free_lexer(&lexer);
			return (print_error_msg("lexer error\n", EXIT_FAILURE));
		}
		print_tokens(lexer.list);
		if (parse(lexer.list) == false)
		{
			free_lexer(&lexer);
			return (print_error_msg("parser error\n", EXIT_FAILURE));
		}
		free_lexer(&lexer);
	}
	return (0);
}
