# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kane <kane@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/04 20:03:14 by kane              #+#    #+#              #
#    Updated: 2024/06/06 15:00:54 by kane             ###   ########.fr        #
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

SRC =  $(addprefix $(SRC_DIR)/, main.c \
		actions.c \
		init.c \
		parsing.c \
		routine.c \
		) \
		$(addprefix $(LIB_DIR)/, ft_atoi.c \
		ft_calloc.c \
		ft_strlen.c \
		ft_usleep.c \
		get_time.c \
		)
		
OBJ = $(addprefix $(OBJ_DIR)/,$(notdir $(SRC:.c=.o)))

vpath %.c $(SRC_DIR) $(LIB_DIR)

all: $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -o $@ -c $<

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -lpthread
	
clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re