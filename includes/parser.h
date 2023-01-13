/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:11:19 by pfrances          #+#    #+#             */
/*   Updated: 2023/01/13 12:41:54 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "libft.h"
# include "ft_printf.h"
# include "lexer.h"
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct s_ast_node
{
	t_token				token;
	struct s_ast_node	*parent;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

t_ast_node	*parser_job();
t_ast_node	*parse_semi_colon(t_ast_node *root, t_lexer *lexer);
t_ast_node	*parse_and_or(t_ast_node *root, t_lexer *lexer);
t_ast_node	*parse_pipe(t_ast_node *root, t_lexer *lexer);
t_ast_node	*parse_input_output(t_ast_node *root, t_lexer *lexer);
t_ast_node	*parse_bracket(t_ast_node *root, t_lexer *lexer);
t_ast_node	*parse_command(t_lexer *lexer);

t_ast_node	*create_node(t_token token);


void		free_syntax_tree(t_ast_node **node);
void		print_syntax_tree(t_ast_node *node);

#endif