# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/17 13:52:28 by pfrances          #+#    #+#              #
#    Updated: 2022/12/29 19:09:07 by pfrances         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -g -Wall -Wextra -Werror
LIBRARY = -L/usr/lib/x86_64-linux-gnu -lreadline
INCLUDE = -I/usr/include/readline/
FT_PRINTF_DIR = ./ft_printf
FT_PRINTF = $(FT_PRINTF_DIR)/ft_printf.a
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
SRCS_DIR = ./
OBJS_DIR = objs
SRCS =	$(addprefix $(SRCS_DIR)/,	main.c					\
									frees.c					\
									ft_split_charset.c		\
									lexer_list.c			\
									lexer_tools.c			\
									lexer.c					\
									manage_tokens.c)
OBJS = $(subst $(SRCS_DIR), $(OBJS_DIR), $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(FT_PRINTF)
	$(CC) $(CFLAGS) $(OBJS) $(LIBRARY) $(INCLUDE) $(LIBFT) $(FT_PRINTF) -o $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(LIBRARY) $(INCLUDE) -c $< -o $@

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