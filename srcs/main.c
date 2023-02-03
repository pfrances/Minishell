/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 12:32:19 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/01 11:28:34 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_msg(t_lexer *lexer)
{
	if (g_state.status == SYNTAX_ERROR)
	{
		ft_putstr_fd(ERROR_SYNTAX_MSG, STDERR_FILENO);
		write(STDERR_FILENO, lexer->input, g_state.error_index);
		write(STDERR_FILENO, "==>", ft_strlen("==>"));
		ft_putendl_fd(lexer->input + g_state.error_index, STDERR_FILENO);
	}
	else if (g_state.status == ALLOCATION_FAILED)
		ft_putendl_fd(ERROR_ALLOCATION_MSG, STDERR_FILENO);
	else if (g_state.status == ENV_ERROR)
		ft_putendl_fd(ENV_ERROR_MSG, STDERR_FILENO);
	else if (g_state.status == PROGRAM_STOP)
		ft_putendl_fd(PROGRAM_STOP_MSG, STDERR_FILENO);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_lexer			lexer;
	t_ast_node		*root;

	(void)argv;
	if (argc == 1)
	{
		set_signal_handling();
		while (1)
		{
			root = parser_job(&lexer, envp);
			if (g_state.status != NORMAL)
				print_error_msg(&lexer);
			else
				execute_ast(root);
			free_all(&lexer, root);
			if (g_state.status == ALLOCATION_FAILED
				|| g_state.status == ENV_ERROR
				|| g_state.status == PROGRAM_STOP)
				return (EXIT_FAILURE);
		}
	}
	return (0);
}
