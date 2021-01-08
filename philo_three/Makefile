# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbroccol <gbroccol@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/07 12:48:43 by gbroccol          #+#    #+#              #
#    Updated: 2021/01/08 13:58:29 by gbroccol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo_three

INCLUDE		= philo_three.h

CC			= gcc -g -Wall -Wextra -Werror

RM			= rm -rf

SRC			= \
				main.c \
				get_time.c \
				action.c \
				eating.c \
				sleeping.c \
				thinking.c \
				init.c \
				pars.c \
				death.c \
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
