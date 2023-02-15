# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/17 13:52:28 by pfrances          #+#    #+#              #
#    Updated: 2023/02/15 21:26:15 by pfrances         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
CFLAGS += -g -fsanitize=address
INCLUDE = -I includes

FT_PRINTF_DIR = ./ft_printf
FT_PRINTF = $(FT_PRINTF_DIR)/ft_printf.a
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

###############################################################################
##################################MAIN#######################################
###############################################################################
SRCS_DIR = ./srcs
OBJS_DIR = ./objs
MAIN_SRCS = $(addprefix $(SRCS_DIR)/,			frees.c						\
												init_shell.c				\
												main.c						\
												signal_handling.c)
MAIN_OBJS = $(subst $(SRCS_DIR), $(OBJS_DIR), $(MAIN_SRCS:.c=.o))
SRCS = $(MAIN_SRCS)
OBJS = $(MAIN_OBJS)
###############################################################################
#################################BUILTINS######################################
###############################################################################
BUILTINS_SRCS_DIR = $(SRCS_DIR)/builtins
BUILTINS_OBJS_DIR = $(OBJS_DIR)/builtins
BUILTINS_SRCS = $(addprefix $(BUILTINS_SRCS_DIR)/,	builtin_cd.c			\
													builtin_echo.c			\
													builtin_env.c			\
													builtin_exit.c			\
													builtin_export.c		\
													builtin_pwd.c			\
													builtin_unset.c			\
													check_builtin_type.c	\
													execute_builtin.c)
BUILTINS_OBJS = $(subst $(BUILTINS_SRCS_DIR), $(BUILTINS_OBJS_DIR), $(BUILTINS_SRCS:.c=.o))
SRCS += $(BUILTINS_SRCS)
OBJS += $(BUILTINS_OBJS)
###############################################################################
#################################COMMANDS######################################
###############################################################################
COMMANDS_SRCS_DIR = $(SRCS_DIR)/commands
COMMANDS_OBJS_DIR = $(OBJS_DIR)/commands
CMD_INIT_DIR = init_cmd
COMMANDS_SRCS = $(addprefix $(COMMANDS_SRCS_DIR)/,	$(CMD_INIT_DIR)/allocate_cmd.c			\
													$(CMD_INIT_DIR)/expand_env_var.c		\
													$(CMD_INIT_DIR)/get_command_path.c		\
													$(CMD_INIT_DIR)/init_cmd.c				\
													$(CMD_INIT_DIR)/set_input_output_args.c	\
													$(CMD_INIT_DIR)/update_cmd_lexem.c		\
													$(CMD_INIT_DIR)/wildcards_match.c		\
													$(CMD_INIT_DIR)/wildcards.c				\
													execute_ast.c			\
													execute_command.c		\
													execute_pipeline.c		\
													here_doc.c				\
													open_files.c			\
													set_reset_redir.c)
COMMANDS_OBJS = $(subst $(COMMANDS_SRCS_DIR), $(COMMANDS_OBJS_DIR), $(COMMANDS_SRCS:.c=.o))
SRCS += $(COMMANDS_SRCS)
OBJS += $(COMMANDS_OBJS)
###############################################################################
################################ENVIRONMENT####################################
###############################################################################
ENVIRONMENT_SRCS_DIR = $(SRCS_DIR)/environment
ENVIRONMENT_OBJS_DIR = $(OBJS_DIR)/environment
ENVIRONMENT_SRCS = $(addprefix $(ENVIRONMENT_SRCS_DIR)/,	add_env_entry.c			\
															check_envp_identifier.c	\
															compose_new_env_entry.c	\
															get_env_path_array.c	\
															get_env_value.c			\
															remove_env_entry.c		\
															search_entry_in_env.c	\
															set_up_envp.c			\
															split_env_var.c			\
															update_all_env.c		\
															update_env_entry.c)
ENVIRONMENT_OBJS = $(subst $(ENVIRONMENT_SRCS_DIR), $(ENVIRONMENT_OBJS_DIR), $(ENVIRONMENT_SRCS:.c=.o))
SRCS += $(ENVIRONMENT_SRCS)
OBJS += $(ENVIRONMENT_OBJS)
###############################################################################
##################################LEXER########################################
###############################################################################
LEXER_SRCS_DIR = $(SRCS_DIR)/lexer
LEXER_OBJS_DIR = $(OBJS_DIR)/lexer
LEXER_SRCS = $(addprefix $(LEXER_SRCS_DIR)/,	get_cmd_line_ending.c		\
												get_next_token.c			\
												get_token_type.c			\
												init_lexer.c				\
												lexer_list.c				\
												redirection_check.c			\
												update_bracket_count.c)
LEXER_OBJS = $(subst $(LEXER_SRCS_DIR), $(LEXER_OBJS_DIR), $(LEXER_SRCS:.c=.o))
SRCS += $(LEXER_SRCS)
OBJS += $(LEXER_OBJS)
###############################################################################
##################################PARSER#######################################
###############################################################################
PARSER_SRCS_DIR = $(SRCS_DIR)/parser
PARSER_OBJS_DIR = $(OBJS_DIR)/parser
PARSER_SRCS = $(addprefix $(PARSER_SRCS_DIR)/,	create_node.c				\
												parse_nodes.c				\
												parser.c)
PARSER_OBJS = $(subst $(PARSER_SRCS_DIR), $(PARSER_OBJS_DIR), $(PARSER_SRCS:.c=.o))
SRCS += $(PARSER_SRCS)
OBJS += $(PARSER_OBJS)
###############################################################################
###################################TOOLS#######################################
###############################################################################
TOOLS_SRCS_DIR = $(SRCS_DIR)/tools
TOOLS_OBJS_DIR = $(OBJS_DIR)/tools
TOOLS_SRCS = $(addprefix $(TOOLS_SRCS_DIR)/,		actualise_exit_status.c	\
													array_tools.c			\
													ft_split_charset.c		\
													quotes_tools.c			\
													strjoin_with_sep.c)
TOOLS_OBJS = $(subst $(TOOLS_SRCS_DIR), $(TOOLS_OBJS_DIR), $(TOOLS_SRCS:.c=.o))
SRCS += $(TOOLS_SRCS)
OBJS += $(TOOLS_OBJS)
###############################################################################

OS = $(shell uname -s)

ifeq ($(OS),Linux)
READLINE = -L/usr/lib/x86_64-linux-gnu -lreadline
INCLUDE += -I/usr/include/readline/
else
READLINE = -L$(shell brew --prefix readline)/lib -lreadline
INCLUDE += -I$(shell brew --prefix readline)/include
endif

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(FT_PRINTF)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) $(READLINE) $(LIBFT) $(FT_PRINTF) -o $(NAME)

$(LEXER_OBJS_DIR)/%.o: $(LEXER_SRCS_DIR)/%.c
	@mkdir -p $(LEXER_OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(PARSER_OBJS_DIR)/%.o: $(PARSER_SRCS_DIR)/%.c
	@mkdir -p $(PARSER_OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(COMMANDS_OBJS_DIR)/$(CMD_INIT_DIR)/%.o: $(COMMANDS_SRCS_DIR)/$(CMD_INIT_DIR)/%.c
	@mkdir -p $(COMMANDS_OBJS_DIR)/$(CMD_INIT_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c  $< -o $@

$(COMMANDS_OBJS_DIR)/%.o: $(COMMANDS_SRCS_DIR)/%.c
	@mkdir -p $(COMMANDS_OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c  $< -o $@

$(ENVIRONMENT_OBJS_DIR)/%.o: $(ENVIRONMENT_SRCS_DIR)/%.c
	@mkdir -p $(ENVIRONMENT_OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c  $< -o $@

$(BUILTINS_OBJS_DIR)/%.o: $(BUILTINS_SRCS_DIR)/%.c
	@mkdir -p $(BUILTINS_OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c  $< -o $@

$(TOOLS_OBJS_DIR)/%.o: $(TOOLS_SRCS_DIR)/%.c
	@mkdir -p $(TOOLS_OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c  $< -o $@

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

bonus: all

install:
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh

update:
	brew update && brew upgrade && brew install readline

.PHONY: all clean fclean re bonus install update