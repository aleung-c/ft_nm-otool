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

HEADER = ./includes/ft_nm_otool.h

SRC = ./ft_nm_src/ft_nm.c \
./ft_nm_src/nm_entry.c \
./ft_nm_src/handle_32.c \
./ft_nm_src/handle_64.c \
./ft_nm_src/handle_fat.c \
./ft_nm_src/handle_ar.c \
./ft_nm_src/nm_sort.c \
./ft_nm_src/display.c \
./ft_nm_src/display_utils.c \
./common_src/handle_fat_searchers.c \
./common_src/utils.c \
./common_src/utils_list.c \
./common_src/utils_list2.c

SRC2 = ./ft_otool_src/ft_otool.c \
./ft_otool_src/otool_entry.c \
./ft_otool_src/handle_32_otool.c \
./ft_otool_src/handle_64_otool.c \
./ft_otool_src/handle_fat_otool.c \
./ft_otool_src/handle_ar_otool.c \
./ft_otool_src/display_otool.c \
./ft_otool_src/display_print_otool.c \
./ft_otool_src/ot_list_utils.c \
./common_src/handle_fat_searchers.c \
./common_src/utils.c \
./common_src/utils_list.c \
./common_src/utils_list2.c

OBJ = $(SRC:.c=.o)
OBJ2 = $(SRC2:.c=.o)

LIB = ./libft/

CC = gcc -g -Wall -Werror -Wextra

all : Lib $(NAME1) $(NAME2)

$(NAME2) : $(OBJ2)
	$(CC) -o $(NAME2) $(OBJ2) -L./libft/ -lft	

$(NAME1) : $(OBJ)
	$(CC) -o $(NAME1) $(OBJ) -L./libft/ -lft

Lib :
	make -C $(LIB)

clean :
	rm -rf $(OBJ)
	rm -rf $(OBJ2)
	cd $(LIB) ; make clean

fclean : clean
	rm -rf $(NAME1)
	rm -rf $(NAME2)
	cd $(LIB) ; make fclean

re : fclean all

.PHONY : all clean fclean re Lib