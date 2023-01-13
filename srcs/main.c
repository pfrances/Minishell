/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 12:32:19 by pfrances          #+#    #+#             */
/*   Updated: 2023/01/11 19:39:02 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// int	print_error_msg(char *error_msg, int exit_status)
// {
// 	write(STDERR_FILENO, error_msg, ft_strlen(error_msg));
// 	return (exit_status);
// }

void	print_syntax_tree(t_ast_node *node)
{
	if (node == NULL)
		return ;
	print_syntax_tree(node->left);
	ft_printf("TOKEN: %s\n", node->token.lexem);
	print_syntax_tree(node->right);
}

int	main(int argc, char *argv[])
{
	t_ast_node	*root;

	(void)argv;
	if (argc == 1)
	{
		root = parser_job();
		if (root == NULL)
			return (EXIT_FAILURE);
	}
	return (0);
}