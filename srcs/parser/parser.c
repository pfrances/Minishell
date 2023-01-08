/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:55:02 by pfrances          #+#    #+#             */
/*   Updated: 2023/01/08 16:13:59 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	print_syntax_tree(t_ast_node *node)
{
	if (node == NULL)
		return ;
	print_syntax_tree(node->left);
	ft_printf("TOKEN: %s\n", node->token.lexem);
	print_syntax_tree(node->right);
}

bool	parse(t_lexer_node	*lexer_list)
{
	t_ast	ast;

	if (lexer_list == NULL)
		return (false);
	ast.root = NULL;
	ast.root = parse_semi_colon(ast.root, &lexer_list);
	if (ast.root == NULL)
		return (false);
	print_syntax_tree(ast.root);
	return (true);
}
