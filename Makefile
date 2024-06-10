# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkane <mkane@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/04 20:03:14 by kane              #+#    #+#              #
#    Updated: 2024/06/10 18:10:59 by mkane            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC_DIR = src
OBJ_DIR = obj
LIB_DIR = lib
INC_DIR = includes

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
RM = rm -rf

SRC =  $(addprefix $(SRC_DIR)/, main.c \
		init.c \
		parsing.c \
		routine.c \
		monitoring.c \
		) \
		$(addprefix $(LIB_DIR)/, ft_atoi.c \
		ft_calloc.c \
		ft_strlen.c \
		ft_usleep.c \
		get_time.c \
		ft_print.c \
		)
		
OBJ = $(addprefix $(OBJ_DIR)/,$(notdir $(SRC:.c=.o)))

vpath %.c $(SRC_DIR) $(LIB_DIR)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -lpthread

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -o $@ -c $<
	
clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re