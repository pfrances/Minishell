# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pfrances <pfrances@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/07 22:35:44 by pfrances          #+#    #+#              #
#    Updated: 2022/12/14 13:07:04 by pfrances         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = get_next_line.a
CFLAGS = -Wall -Wextra -Werror
SRCS_DIR = srcs
OBJS_DIR = objs
SRCS = $(addprefix $(SRCS_DIR)/, get_next_line.c get_next_line_utils.c)
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