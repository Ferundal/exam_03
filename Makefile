# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cjettie <cjettie@21-school.ru>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/05 14:46:25 by cjettie           #+#    #+#              #
#    Updated: 2020/11/16 17:00:42 by cjettie          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADER=				${wildcard ./headers/*.h}

HEADERDIR=

SRCS=				main.c


TURNIN=				${HEADER} ${SRCS}

NORMO=				${TURNIN}

OBJS=				${SRCS:.c=.o}

NAME=				micro_paint

CC=					cc
RM=					rm -f
AR=					ar -r

CFLAGS=				-Wall -Wextra -Werror -g

NORM=				norminette

all:				${NAME}

.c.o:
					${CC} ${CFLAGS} ${HEADERDIR} -c $< -o ${<:.c=.o}

ifndef COMPILE_BONUS
${NAME}:			${OBJS}
					${CC} -o ${NAME} ${OBJS} ${LIBFT} ${LIBMLX}
else
${NAME}:			${OBJS}
					${CC} -o ${NAME} ${OBJS} ${LIBFT} ${LIBMLX}
endif

bonus:
					${MAKE} COMPILE_BONUS=1 all

clean:
					${RM} ${OBJS} ${OBJS_B}

fclean:
					${RM} ${OBJS} ${OBJS_B}
					${RM} ${NAME}

norm:		
					${NORM} ${NORMO}

re:					fclean all

.PHONY:				all clean fclean re bonus
