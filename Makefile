# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clara <clara@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/23 12:00:49 by chugot            #+#    #+#              #
#    Updated: 2023/07/26 17:48:26 by clara            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	pipex

SRCS =	pipex.c \

CC = gcc

FLAGS =	-g -Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o)

$(NAME):	$(OBJS)
			$(CC)  $(FLAGS) $(OBJS) -o $(NAME)

all:	$(NAME)

clean:
		rm -f $(OBJS)

fclean:
		rm -f $(OBJS) $(NAME)

re:		fclean $(NAME)

.PHONY:	all clean fclean re
