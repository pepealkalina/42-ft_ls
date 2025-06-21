# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: preina-g <preina-g@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/08 11:52:09 by pepealkalin       #+#    #+#              #
#    Updated: 2025/06/21 12:21:42 by preina-g         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC = main.c utils.c print_large.c 42-Ft_printf/src/ft_printf.c 42-Ft_printf/src/ft_printf_utils.c

OBJECTS = $(SRC:.c=.o)

CC = gcc

CCFLAGS = -Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): $(OBJECTS) $(INCLUDE)
	$(CC) $(CCFLAGS) $(OBJECTS) -o $(NAME)

%.o: %.c
	$(CC) $(CCFLAGS) -c -o $@ $<

clean:
	rm -rf *.o

fclean:
	rm -rf *.o $(NAME)

re:	fclean all

rebonus: fclean all