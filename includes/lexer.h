/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 12:34:20 by pfrances          #+#    #+#             */
/*   Updated: 2023/01/07 16:23:05 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "libft.h"
# include "ft_printf.h"
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

# define SPACES_CHARSET " \n\t\v\f\r"
# define TOKENS_CHARSET "<< < >> > && & || | ; ( )"
# define TOKENS_LEN_MAX 2
# define PROMPT_INDENT " > "

typedef enum e_token_types
{
	TOKEN_INPUT_STD,
	TOKEN_INPUT,
	TOKEN_OUTPUT_ADD,
	TOKEN_OUTPUT,
	TOKEN_AND,
	TOKEN_BG_JOB,
	TOKEN_OR,
	TOKEN_PIPE,
	TOKEN_SEMICOLON,
	TOKEN_OPEN_BRACKET,
	TOKEN_CLOSE_BRACKET,
	TOKEN_COMMAND,
	TOKEN_EOF
}		t_token_types;

typedef struct s_token
{
	t_token_types	type;
	char			*lexem;
}	t_token;

typedef struct s_lexer_node
{
	t_token				token;
	struct s_lexer_node	*next;
}	t_lexer_node;

typedef struct s_lexer
{
	t_lexer_node	*list;
	char			*input;
	size_t			index;
	int				bracket_count;
	t_token_types	current_token_type;
	char			**tkn_types_array;
}	t_lexer;

/*				lexer.c					*/
bool			lexer_job(t_lexer *lexer);

/*				lexer_list.c			*/
bool			add_node_to_list(t_lexer *lexer, size_t len);

/*				lexer_tools.c			*/
t_token_types	get_token_type(t_lexer *lexer, size_t index);
char			**split_in_tokens(char *input);
void			print_tokens(t_lexer_node *tokens);
bool			read_new_line(t_lexer *lexer);

/*				manage_tokens.c			*/
bool			manage_tokens(t_lexer *lexer);

/*				ft_split_charset.c		*/
char			**ft_split_charset(char *input, const char *charset);

/*				frees.c					*/
void			free_array(void **array);
void			free_lexer_list(t_lexer_node *list);
void			free_lexer(t_lexer *lexer);

#endif