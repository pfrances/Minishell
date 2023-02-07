/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 12:32:19 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/07 16:34:03 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_msg(t_lexer *lexer)
{
	if (g_state.error_state == SYNTAX_ERROR)
	{
		ft_putstr_fd(ERROR_SYNTAX_MSG, STDERR_FILENO);
		write(STDERR_FILENO, lexer->input, g_state.error_index);
		write(STDERR_FILENO, "==>", 3);
		ft_putendl_fd(lexer->input + g_state.error_index, STDERR_FILENO);
	}
	else if (g_state.error_state == ALLOCATION_FAILED)
		ft_putendl_fd(ERROR_ALLOCATION_MSG, STDERR_FILENO);
	else if (g_state.error_state == ENV_ERROR)
		ft_putendl_fd(ENV_ERROR_MSG, STDERR_FILENO);
	else if (g_state.error_state == PROGRAM_STOP)
		ft_putendl_fd(PROGRAM_STOP_MSG, STDERR_FILENO);
}

void	get_current_pid(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		exit(0);
	else if (pid > 0)
	{
		g_state.main_pid_str = ft_itoa(pid);
		if (g_state.main_pid_str == NULL)
		{
			ft_putendl_fd(ERROR_ALLOCATION_MSG, STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		return ;
	}
	perror("fork failed");
	exit(EXIT_FAILURE);
}

void	actualise_exit_status(int status)
{
	g_state.last_pgrm_exit_status = status;
	free(g_state.last_pgrm_exit_status_str);
	g_state.last_pgrm_exit_status_str = ft_itoa(status);
	if (g_state.last_pgrm_exit_status_str == NULL)
		g_state.error_state = ALLOCATION_FAILED;
}

void	first_init(t_lexer *lexer, t_ast_node **root, char *envp[])
{
	*root = NULL;
	get_current_pid();
	g_state.last_pgrm_exit_status_str = NULL;
	actualise_exit_status(0);
	g_state.stop_signal_flag = false;
	rl_done = 0;
	set_signal_handling();
	lexer->envp = envp;
	lexer->tkn_types_array = ft_split_charset(TOKENS_CHARSET, SPACES_CHARSET);
	if (lexer->tkn_types_array == NULL)
		g_state.error_state = ALLOCATION_FAILED;
	lexer->all_path = ft_split(getenv("PATH"), ':');
	if (lexer->all_path == NULL)
		g_state.error_state = ALLOCATION_FAILED;
	lexer->list_head = NULL;
	lexer->input = NULL;
	if (g_state.error_state == ALLOCATION_FAILED)
	{
		free_all(lexer, *root);
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_lexer		lexer;
	t_ast_node	*root;

	(void)argv;
	if (argc == 1)
	{
		first_init(&lexer, &root, envp);
		while (1)
		{
			root = parser_job(&lexer);
			if (g_state.error_state != NO_ERROR)
				print_error_msg(&lexer);
			else
				execute_ast(root);
			free_all(&lexer, root);
			if (g_state.error_state >= ALLOCATION_FAILED)
				return (EXIT_FAILURE);
		}
	}
	return (0);
}
