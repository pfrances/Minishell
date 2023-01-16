/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 12:32:19 by pfrances          #+#    #+#             */
/*   Updated: 2023/01/16 12:01:06 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	print_error_msg(t_lexer *lexer)
{
	ft_putstr_fd(ERROR_SYNTAX_MSG, STDERR_FILENO);
	ft_putendl_fd(lexer->current_token.lexem, STDERR_FILENO);
}

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
	t_lexer		lexer;
	t_ast_node	*root;

	(void)argv;
	if (argc == 1)
	{
		root = parser_job(&lexer);
		if (root == NULL)
			return (EXIT_FAILURE);
		free_syntax_tree(&root);
		free_lexer(&lexer);
	}
	return (0);
}
