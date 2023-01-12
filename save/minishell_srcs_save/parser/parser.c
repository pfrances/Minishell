/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:55:02 by pfrances          #+#    #+#             */
/*   Updated: 2023/01/09 19:43:01 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_syntax_tree(t_ast_node *node)
{
	if (node == NULL)
		return ;
	free_syntax_tree(node->left);
	free_syntax_tree(node->right);
	free(node);
	node = NULL;
}

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
	if (ast.root == NULL || lexer_list != NULL)
		return (false);
	print_syntax_tree(ast.root);
	free_syntax_tree(ast.root);
	return (true);
}
