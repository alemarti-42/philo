# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alemarti <alemarti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/09 15:21:03 by alemarti          #+#    #+#              #
#    Updated: 2022/12/21 18:26:51 by alemarti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	philo.c 		\
				init_philo.c	\
				utils.c			\
				routine_utils.c	\
				stop.c


OBJS		= ${SRCS:.c=.o}

NAME		= philo

CC			= gcc
RM			= rm -f
CFLAGS		= -Wall -Werror -Wextra 

all:	$(NAME)

${NAME}:	${OBJS}
			${CC} ${CFLAGS} ${OBJS} -pthread -o ${NAME}

			
clean:
			@${RM} ${OBJS}


fclean:		clean
			@${RM} ${NAME}
				
re:		fclean all

.PHONY: all bonus clean fclean re
