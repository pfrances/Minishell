/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 12:32:19 by pfrances          #+#    #+#             */
/*   Updated: 2023/01/17 11:18:19 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	print_error_msg(t_lexer *lexer)
{
	if (lexer->error.type == SYNTAX_ERROR)
	{
		ft_putstr_fd(ERROR_SYNTAX_MSG, STDERR_FILENO);
		write(STDERR_FILENO, lexer->input, lexer->error.index);
		write(STDERR_FILENO, "==>", ft_strlen("==>"));
		ft_putendl_fd(lexer->input + lexer->error.index, STDERR_FILENO);
	}
	else if (lexer->error.type == ALLOCATION_FAILED)
		ft_putendl_fd(ERROR_ALLOCATION_MSG, STDERR_FILENO);
}

void	print_tokens(t_lexer_node *list)
{
	while (list != NULL)
	{
		ft_printf("%s", list->token.lexem);
		list = list->next;
		if (list != NULL)
			ft_printf("-->");
		else
			ft_printf("\n");
	}
}

void	print_syntax_tree(t_ast_node *node)
{
	if (node == NULL)
		return ;
	print_syntax_tree(node->left);
	ft_printf("TOKEN: %s\n", node->token->lexem);
	print_syntax_tree(node->right);
}

int	main(int argc, char *argv[])
{
	t_lexer		lexer;
	t_ast_node	*root;

	(void)argv;
	if (argc == 1)
	{
		while (1)
		{
			root = parser_job(&lexer);
			if (lexer.error.type == ALLOCATION_FAILED)
				return (EXIT_FAILURE);
			free_syntax_tree(&root);
			free_lexer(&lexer);
		}
	}
	return (0);
}
