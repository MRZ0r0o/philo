# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 02:13:31 by mradwan           #+#    #+#              #
#    Updated: 2023/01/29 17:44:40 by mradwan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS =	philo.c					\
		philo_utils.c			\
		philo_helper.c			\
		parse.c					\
		philo_routien.c
		


OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -g3 -Wall -Wextra -Werror# -fsanitize=thread

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lpthread

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
