# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/21 18:18:48 by ykoh              #+#    #+#              #
#    Updated: 2020/10/01 13:01:41 by ykoh             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	ft_printf.c\
				set_fs.c\
				manage_length.c\
				manage_length_n.c\
				manage_precision.c\
				manage_flags.c\
				manage_width.c\
				put_specifier.c\
				put_specifier_s.c\
				put_specifier_utils.c

OBJS		=	$(SRCS:.c=.o)

NAME		=	libftprintf.a
LIBFT		=	libft
RM			=	rm -f
LIB			=	ar rcu
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror

$(NAME) :	$(OBJS)
			$(MAKE) all -C $(LIBFT)/
			cp $(LIBFT)/$(LIBFT).a $(NAME)
			$(LIB) $@ $^

all		:	$(NAME)

clean	:
			$(MAKE) clean -C $(LIBFT)/
			$(RM) $(OBJS)

fclean	:	clean
			$(RM) $(LIBFT)/$(LIBFT).a
			$(RM) $(NAME)

re		:	fclean all

bonus	:	all

.PHONY	:	all clean fclean re bonus
