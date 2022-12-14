# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/07 22:35:44 by pfrances          #+#    #+#              #
#    Updated: 2022/12/07 13:28:26 by pfrances         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_printf.a
CFLAGS = -Wall -Wextra -Werror
SRCS_DIR = srcs
OBJS_DIR = objs
SRCS = $(addprefix $(SRCS_DIR)/, ft_printf.c ft_printf_utils.c)
OBJS = $(subst $(SRCS_DIR), $(OBJS_DIR), $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	ar -rcs $(NAME) $(OBJS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re