/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 12:32:00 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/01 09:23:06 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "ft_printf.h"
# include "libft.h"
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>

# define BUFFER_SIZE 256
# define SPACES_CHARSET " \n\t\v\f\r"
# define TOKENS_CHARSET "&& || | ; ( )"
# define TOKENS_LEN_MAX 2
# define PROMPT_MINISHELL "Minishell > "
# define PROMPT_INDENT " > "
# define ERROR_SYNTAX_MSG "	Syntax error - unexpected token: "
# define ERROR_ALLOCATION_MSG "	Failed to allocate memory"
# define ENV_ERROR_MSG "	Failed to deal with environment variable"
# define PROGRAM_STOP_MSG "exit"

/******************************************************************************/
/**********************************cmd_struct**********************************/
/******************************************************************************/
typedef enum e_input_output_enum
{
	FILE_INPUT,
	FILE_OUTPUT,
	STD_INPUT,
	FILE_ADD_OUTPUT
}	t_input_output_enum;

typedef struct s_input_output
{
	t_input_output_enum	type;
	char				*filename;
	int					fd;
}	t_input_output;

typedef struct s_command_cnt
{
	size_t	input_output_cnd;
	size_t	args_cnt;
}	t_cmd_cnt;

typedef struct s_cmd
{
	char				*path;
	char				**args;
	t_input_output		**input_output;
	int					input_fd;
	int					input_fd_save;
	int					output_fd;
	int					output_fd_save;
	char				**all_path;
	char				**envp;
}	t_cmd;
/******************************************************************************/
/**********************************ast_struct**********************************/
/******************************************************************************/
typedef enum e_token_types
{
	AND,
	OR,
	PIPE,
	SEMICOLON,
	OPEN_BRACKET,
	CLOSE_BRACKET,
	COMMAND,
	_EOF
}	t_token_types;

typedef struct s_token
{
	t_token_types	type;
	char			*lexem;
}	t_token;

typedef struct s_ast_node
{
	t_token				*token;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	t_cmd				*cmd;
}	t_ast_node;
/******************************************************************************/
/**********************************lexer_struct********************************/
/******************************************************************************/
typedef struct s_lexer_node
{
	t_token				token;
	struct s_lexer_node	*prev;
	struct s_lexer_node	*next;
}	t_lexer_node;

typedef struct s_lexer
{
	t_lexer_node	*list_head;
	char			*input;
	size_t			index;
	int				bracket_count;
	t_token_types	current_token_type;
	t_token			*current_token;
	t_lexer_node	*current_node;
	char			**tkn_types_array;
	char			**envp;
	char			**all_path;
}	t_lexer;
/******************************************************************************/
/**********************************state_struct*******************************/
/******************************************************************************/
typedef enum e_status_enum
{
	NORMAL,
	ALLOCATION_FAILED,
	SYNTAX_ERROR,
	ENV_ERROR,
	CMD_STOP,
	PROGRAM_STOP
}	t_status_enum;

typedef struct s_pgrm_state
{
	t_status_enum	status;
	size_t			error_index;
	bool			pgrm_is_running;
	bool			stop_signal_flag;
	bool			wait_endline;
}	t_pgrm_state;
/*		GLOBAL VARIABLE TO CURRENT STATE		*/
t_pgrm_state	g_state;

/******************************************************************************/
/*************************************srcs*************************************/
/******************************************************************************/
/*				main.c					*/
void			print_error_msg(t_lexer *lexer);
/*				signal_handling.c		*/
void			set_signal_handling(void);
/*				frees.c*/
void			free_all(t_lexer *lexer, t_ast_node *ast_root);
/*				ft_split_charset.c		*/
char			**ft_split_charset(char *input, const char *charset);
/*				read_from_stdin.c		*/
char			*read_from_stdin(char *prompt_msg);
/******************************************************************************/
/**********************************srcs/lexer**********************************/
/******************************************************************************/
/*				lexer.c					*/
bool			init_lexer(t_lexer *lexer, char *emvp[]);
/*				lexer_list.c			*/
bool			add_node_to_list(t_lexer *lexer, size_t len);
t_lexer_node	*last_lexer_list(t_lexer_node *node);
/*				lexer_tools.c			*/
t_token_types	get_token_type(t_lexer *lexer, size_t index);
void			update_bracket_count(t_lexer *lexer);
bool			get_command_line_ending(t_lexer *lexer);
/*				get_next_token.c			*/
bool			get_next_token(t_lexer *lexer);
/*				redirection_check.c			*/
bool			check_redirection(t_lexer *lexer, char *cmd, size_t len);
/******************************************************************************/
/*********************************srcs/parser**********************************/
/******************************************************************************/
/*				parser.c					*/
t_ast_node		*parser_job(t_lexer *lexer, char *envp[]);
/*				parse_nodes.c				*/
t_ast_node		*parse_semi_colon(t_ast_node *root, t_lexer *lexer);
/*				create_nodes.c				*/
t_ast_node		*create_node(t_lexer *lexer);
/*				get_command_path.c			*/
char			*get_cmd_path(char *name, char **env_paths);
/*				set_input_output_args.c		*/
void			set_input_output_args(t_cmd *cmd, char *lexem);
/******************************************************************************/
/********************************srcs/commands*********************************/
/******************************************************************************/
/*				command_execute.c		*/
int				execute_command(t_cmd *cmd);
/*				execute_ast.c			*/
int				execute_ast(t_ast_node *node);
/******************************************************************************/
#endif