# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pfrances <pfrances@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/17 13:52:28 by pfrances          #+#    #+#              #
#    Updated: 2022/12/14 17:14:53 by pfrances         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = #-Wall -Wextra -Werror
LIBFLAGS = -L$(shell brew --prefix readline)/lib -lreadline
INCLUDE = -I minishell.h
FT_PRINTF_DIR = ./ft_printf
FT_PRINTF = $(FT_PRINTF_DIR)/ft_printf.a
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
GNL_DIR = ./get_next_line
GNL = $(GNL_DIR)/get_next_line.a
SRCS_DIR = ./
OBJS_DIR = objs
SRCS =	$(addprefix $(SRCS_DIR)/,	main.c					\
									frees.c					\
									ft_split_charset.c		\
									lexer.c)
OBJS = $(subst $(SRCS_DIR), $(OBJS_DIR), $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(FT_PRINTF) $(GNL)
	$(CC) $(CFLAGS) $(LIBFLAGS) $(INCLUDE) $(OBJS) $(LIBFT) $(FT_PRINTF) $(GNL) -o $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(LIBFLAGS) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR) bonus

$(FT_PRINTF):
	make -C $(FT_PRINTF_DIR)

$(GNL):
	make -C $(GNL_DIR)

clean:
	rm -rf $(OBJS_DIR)
	make -C $(LIBFT_DIR) clean
	make -C $(FT_PRINTF_DIR) clean
	make -C $(GNL_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)
	rm -f $(FT_PRINTF)
	rm -f $(GNL)

re: fclean all

.PHONY: all clean fclean re