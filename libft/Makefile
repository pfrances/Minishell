# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/05 08:33:13 by pfrances          #+#    #+#              #
#    Updated: 2022/12/07 13:29:43 by pfrances         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CFLAGS = -Wall -Wextra -Werror
SRCS_DIR = srcs
OBJS_DIR = objs
SRCS =	$(addprefix $(SRCS_DIR)/,	ft_isalpha.c		\
									ft_isdigit.c		\
									ft_isalnum.c		\
									ft_isascii.c		\
									ft_isprint.c		\
									ft_strlen.c			\
									ft_memset.c			\
									ft_bzero.c			\
									ft_memcpy.c			\
									ft_memmove.c		\
									ft_strlcpy.c		\
									ft_strlcat.c		\
									ft_toupper.c		\
									ft_tolower.c		\
									ft_strchr.c			\
									ft_strrchr.c		\
									ft_strncmp.c		\
									ft_memchr.c			\
									ft_memcmp.c			\
									ft_strnstr.c		\
									ft_atoi.c			\
									ft_calloc.c			\
									ft_strdup.c			\
									ft_strndup.c		\
									ft_substr.c			\
									ft_strjoin.c		\
									ft_strtrim.c		\
									ft_split.c			\
									ft_itoa.c			\
									ft_strmapi.c		\
									ft_striteri.c		\
									ft_putchar_fd.c		\
									ft_putstr_fd.c		\
									ft_putendl_fd.c		\
									ft_putnbr_fd.c)
B_SRCS = $(addprefix $(SRCS_DIR)/,	ft_lstnew.c 		\
									ft_lstadd_front.c	\
									ft_lstsize.c		\
									ft_lstlast.c		\
									ft_lstadd_back.c	\
									ft_lstdelone.c		\
									ft_lstclear.c		\
									ft_lstiter.c		\
									ft_lstmap.c)
OBJS = $(subst $(SRCS_DIR), $(OBJS_DIR), $(SRCS:.c=.o))
B_OBJS = $(subst $(SRCS_DIR), $(OBJS_DIR), $(B_SRCS:.c=.o))
INCLUDES = -I ./includes

ifdef WITH_BONUS
	OBJS += $(B_OBJS)
endif

all: $(NAME)

$(NAME): $(OBJS)
	ar -rcs $(NAME) $(OBJS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

bonus:
	make all WITH_BONUS=TRUE

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus