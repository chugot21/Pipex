# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clara <clara@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/23 12:00:49 by chugot            #+#    #+#              #
#    Updated: 2023/07/23 19:36:04 by clara            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	pipex

SRCS =	pipex.c \
		#utils !

CC = cc

FLAGS =	-g -Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o)

//MLX_LIB	= ./minilibx-linux/libmlx.a

//MLX_FLAG =	-lX11 -lXext

//MLX_EX =	$(MLX_LIB) $(MLX_FLAG)


all:	$(NAME)

$(NAME):	$(OBJS)
			$(CC)  $(FLAGS) $(OBJS) $(SRCS) -o $(NAME)
clean:
		rm -f $(OBJS)

fclean:
		rm -f $(OBJS) $(NAME)

re:		fclean $(NAME)

.PHONY:	all clean fclean re
