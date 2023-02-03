# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/17 13:52:28 by pfrances          #+#    #+#              #
#    Updated: 2023/01/31 12:59:26 by pfrances         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
INCLUDE = -I includes -I/usr/include/readline/

FT_PRINTF_DIR = ./ft_printf
FT_PRINTF = $(FT_PRINTF_DIR)/ft_printf.a
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS_DIR = ./srcs
OBJS_DIR = ./objs
MAIN_SRCS = $(addprefix $(SRCS_DIR)/,			main.c						\
												frees.c						\
												signal_handling.c			\
												ft_split_charset.c			\
												read_from_stdin.c)
MAIN_OBJS = $(subst $(SRCS_DIR), $(OBJS_DIR), $(MAIN_SRCS:.c=.o))
SRCS = $(MAIN_SRCS) $(LEXER_SRCS) $(PARSER_SRCS) $(COMMANDS_SRCS)
OBJS = $(MAIN_OBJS) $(LEXER_OBJS) $(PARSER_OBJS) $(COMMANDS_OBJS)

##################################LEXER########################################
LEXER_SRCS_DIR = $(SRCS_DIR)/lexer
LEXER_OBJS_DIR = $(OBJS_DIR)/lexer
LEXER_SRCS = $(addprefix $(LEXER_SRCS_DIR)/,	get_next_token.c			\
												lexer_init.c				\
												lexer_list.c				\
												lexer_tools.c				\
												redirection_check.c)
LEXER_OBJS = $(subst $(LEXER_SRCS_DIR), $(LEXER_OBJS_DIR), $(LEXER_SRCS:.c=.o))
###############################################################################
##################################PARSER########################################
PARSER_SRCS_DIR = $(SRCS_DIR)/parser
PARSER_OBJS_DIR = $(OBJS_DIR)/parser
PARSER_SRCS = $(addprefix $(PARSER_SRCS_DIR)/,	create_node.c				\
												get_command_path.c			\
												parse_nodes.c				\
												parser.c					\
												set_input_output_args.c)
PARSER_OBJS = $(subst $(PARSER_SRCS_DIR), $(PARSER_OBJS_DIR), $(PARSER_SRCS:.c=.o))
###############################################################################
#################################COMMANDS######################################
COMMANDS_SRCS_DIR = $(SRCS_DIR)/commands
COMMANDS_OBJS_DIR = $(OBJS_DIR)/commands
COMMANDS_SRCS = $(addprefix $(COMMANDS_SRCS_DIR)/,	command_execute.c	\
													execute_ast.c)
COMMANDS_OBJS = $(subst $(COMMANDS_SRCS_DIR), $(COMMANDS_OBJS_DIR), $(COMMANDS_SRCS:.c=.o))
###############################################################################
OS = $(shell uname -s)

ifeq ($(OS),Linux)
READLINE = -L/usr/lib/x86_64-linux-gnu -lreadline
else
READLINE = -L$(shell brew --prefix readline)/lib -lreadline
endif

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(FT_PRINTF)
	$(CC) $(CFLAGS) $(OBJS) $(READLINE) $(INCLUDE) $(LIBFT) $(FT_PRINTF) -o $(NAME)

$(LEXER_OBJS_DIR)/%.o: $(LEXER_SRCS_DIR)/%.c
	@mkdir -p $(LEXER_OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(PARSER_OBJS_DIR)/%.o: $(PARSER_SRCS_DIR)/%.c
	@mkdir -p $(PARSER_OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(COMMANDS_OBJS_DIR)/%.o: $(COMMANDS_SRCS_DIR)/%.c
	@mkdir -p $(COMMANDS_OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR) bonus

$(FT_PRINTF):
	make -C $(FT_PRINTF_DIR)

clean:
	rm -rf $(OBJS_DIR)
	make -C $(LIBFT_DIR) clean
	make -C $(FT_PRINTF_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)
	rm -f $(FT_PRINTF)

re: fclean all

.PHONY: all clean fclean re