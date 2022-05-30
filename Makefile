# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kalmheir <kalmheir@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/15 16:46:57 by kalmheir          #+#    #+#              #
#    Updated: 2022/05/30 19:02:08 by kalmheir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	ft_printf/ft_printf0.c ft_printf/ft_printf1.c ft_printf/printers.c
OBJS	= ${SRCS:.c=.o}
NAME	= libftprintf.a
LIBC	= ar rc
LIBR	= ranlib
CC		= gcc
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	${LIBC} ${NAME} ${OBJS}
	${LIBR} ${NAME}

all: ${NAME}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

norm:
	norminette -R CheckForbiddenSourceHeader */*.[ch]
