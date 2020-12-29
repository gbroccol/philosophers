# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbroccol <gbroccol@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/07 12:48:43 by gbroccol          #+#    #+#              #
#    Updated: 2020/12/29 15:51:58 by gbroccol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo_one

INCLUDE		= philo_one.h

CC			= gcc -g -Wall -Wextra -Werror

RM			= rm -rf

SRC			= \
				main.c \
				init.c \
				pars.c \
				die.c \
				putnbr.c \
				libft.c
					
OBJ			= $(SRC:.c=.o)

all: $(OBJ)
	@$(CC) -I./ $(OBJ) -o philo_one
clean:
	@$(RM) $(NAME)
fclean: clean
	@$(RM) $(OBJ)
re: fclean all

.PHONY: all clean fclean re
