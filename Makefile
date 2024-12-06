# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pepealkalina <pepealkalina@student.42.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/08 11:52:09 by pepealkalin       #+#    #+#              #
#    Updated: 2024/11/11 13:09:37 by pepealkalin      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC = main.c utils.c

OBJECTS = $(SRC:.c=.o)

CC = gcc

CCFLAGS = -Wall -Wextra -Werror

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