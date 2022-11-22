# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbasilio <jbasilio@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/21 03:20:28 by jbasilio          #+#    #+#              #
#    Updated: 2022/11/21 03:20:35 by jbasilio         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = server client

SRC = server.c client.c
OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
REMOVE = rm -f

all: $(NAME)

bonus: all

server: server.o
	@make -s -C libft
	@$(CC) -o $@ $< -Llibft -lft

client: client.o
	@make -s -C libft
	@$(CC) -o $@ $< -Llibft -lft

%.o: %.c
	@$(CC) -c $(CFLAGS) $^

clean:
	@$(REMOVE) $(OBJ)
	@make -s -C libft clean
	
fclean: clean
	@$(REMOVE) server client libft/libft.a

re: fclean all

.PHONY: all bonus clean fclean re
