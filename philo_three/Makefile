# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbroccol <gbroccol@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/07 12:48:43 by gbroccol          #+#    #+#              #
#    Updated: 2021/01/12 16:32:31 by gbroccol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ./philo_three 4 310 200 100 1

NAME		= philo_three

INCLUDE		= philo_three.h

CC			= gcc -g -Wall -Wextra -Werror

RM			= rm -rf

SRC			= \
				main.c \
				get_time.c \
				action.c \
				init.c \
				pars.c \
				phil_death.c \
				putnbr.c \
				libft.c
					
OBJ			= $(SRC:.c=.o)

all: $(OBJ)
	@$(CC) -I./ $(OBJ) -o philo_three
clean:
	@$(RM) $(OBJ)
fclean: clean
	@$(RM) $(NAME)
re: fclean all

.PHONY: all clean fclean re
