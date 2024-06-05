# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kane <kane@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/04 20:03:14 by kane              #+#    #+#              #
#    Updated: 2024/06/04 20:12:21 by kane             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosopher

SRC_DIR = src
OBJ_DIR = obj
LIB_DIR = lib
INC_DIR = includes

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
RM = rm -rf

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

vpath %.c $(SRC_DIR) $(LIB_DIR)

SRC = main.c \

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -lpthread

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -o $@ -c $<

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re