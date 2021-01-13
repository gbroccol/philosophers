# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbroccol <gbroccol@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/07 12:48:43 by gbroccol          #+#    #+#              #
#    Updated: 2021/01/12 18:07:27 by gbroccol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo_one

INCLUDE		= philo_one.h

CC			= gcc -g -Wall -Wextra -Werror -pthread

RM			= rm -rf

SRC			= \
				action.c \
				ft_atoi.c \
				get_time.c \
				init.c \
				main.c \
				pars.c \
				phil_die.c \
				putnbr.c
					
OBJ			= $(SRC:.c=.o)

all: $(OBJ)
	@$(CC) -I./ $(OBJ) -o philo_one
clean:
	@$(RM) $(OBJ)
fclean: clean
	@$(RM) $(NAME)
re: fclean all

.PHONY: all clean fclean re
