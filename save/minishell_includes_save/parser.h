/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:11:19 by pfrances          #+#    #+#             */
/*   Updated: 2023/01/11 13:00:04 by pfrances         ###   ########.fr       */
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

typedef struct s_ast
{
	t_ast_node	*root;
	size_t		depth;
}	t_ast;

bool		parser_job(t_lexer_node	*lexer_list);
t_ast_node	*parse_semi_colon(t_ast_node *root, t_lexer_node **lexer_list);

t_ast_node	*create_node(t_token token);
t_ast_node	*parse_input_output(t_ast_node *root, t_lexer_node **lexer_list);

#endif