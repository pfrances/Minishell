/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 12:32:19 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/10 10:42:13 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_msg(t_lexer *lexer)
{
	if (g_state.error == SYNTAX_ERROR)
	{
		ft_putstr_fd(ERROR_SYNTAX_MSG, STDERR_FILENO);
		write(STDERR_FILENO, lexer->input, g_state.error_index);
		write(STDERR_FILENO, "==>", 3);
		ft_putendl_fd(lexer->input + g_state.error_index, STDERR_FILENO);
	}
	else if (g_state.error == MALLOC_FAILED)
		ft_putendl_fd(ERROR_ALLOCATION_MSG, STDERR_FILENO);
	else if (g_state.error == PROGRAM_STOP)
		ft_putendl_fd(PROGRAM_STOP_MSG, STDERR_FILENO);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_lexer		lexer;
	t_ast_node	*root;

	(void)argv;
	if (argc == 1)
	{
		init_shell(&lexer, &root, envp);
		while (1)
		{
			root = parser_job(&lexer);
			execute_ast(root);
			if (g_state.error != NO_ERROR)
				print_error_msg(&lexer);
			free_all(&lexer, root);
			if (g_state.error >= MALLOC_FAILED)
				return (g_state.exit_status);
		}
	}
	return (0);
}
