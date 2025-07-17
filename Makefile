# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pepealkalina <pepealkalina@student.42.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/08 11:52:09 by pepealkalin       #+#    #+#              #
#    Updated: 2025/07/10 13:54:25 by pepealkalin      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC = main.c utils.c print_large.c ft_printf/src/ft_printf.c ft_printf/src/ft_printf_utils.c

OBJECTS = $(SRC:.c=.o)

CC = gcc

CCFLAGS = -Wall -Wextra -Werror -g

all: $(NAME)
	

$(NAME): $(OBJECTS) $(INCLUDE)
	$(CC) $(CCFLAGS) $(OBJECTS) -o $(NAME) 

%.o: %.c
	$(CC) $(CCFLAGS) -c -o $@ $<

clean:
	rm -rf *.o ft_printf/src/ft_printf.o ft_printf/src/ft_printf_utils.o

fclean:
	rm -rf *.o ft_printf/src/ft_printf.o ft_printf/src/ft_printf_utils.o $(NAME)

re:	fclean all

rebonus: fclean all