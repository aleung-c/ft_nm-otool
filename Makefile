# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/23 18:07:27 by aleung-c          #+#    #+#              #
#    Updated: 2016/05/23 18:07:30 by aleung-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME1 = ft_nm

NAME2 = ft_otool

HEADER = ft_nm_otool.h

SRC = ft_nm.c \
utils.c

OBJ = $(SRC:.c=.o)

LIB = ./libft/

CC = gcc -g -Wall -Werror -Wextra

all : Lib $(NAME1) 


$(NAME1) : $(OBJ)
	$(CC) -o $(NAME1) $(OBJ) -L./libft/ -lft

Lib :
	make -C $(LIB)

clean :
	rm -rf $(OBJ)
	cd $(LIB) ; make clean

fclean : clean
	rm -rf $(NAME1)
	cd $(LIB) ; make fclean

re : fclean all

.PHONY : all clean fclean re