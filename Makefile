# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/21 18:18:48 by ykoh              #+#    #+#              #
#    Updated: 2020/07/13 22:56:20 by ykoh             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	ft_printf.c\
				set_meta_data.c\
				put_utils_char.c\
				put_utils_wchar.c\
				put_specifier_percent.c\
				put_specifier_n.c\
				put_specifier_c.c\
				put_specifier_s.c\
				put_specifier_di.c\
				put_specifier_u.c\
				put_specifier_x.c\
				put_specifier_p.c\
				put_specifier_efg.c\
				put_specifier_efg_select.c

OBJS		=	$(SRCS:.c=.o)

NAME		=	libftprintf.a
LIBFT		=	libft
RM			=	rm -f
LIB			=	ar rcu

$(NAME) :	$(OBJS)
			make all -C $(LIBFT)/
			cp $(LIBFT)/$(LIBFT).a $(NAME)
			$(LIB) $@ $^

all		:	$(NAME)

clean	:
			make clean -C $(LIBFT)/
			$(RM) $(OBJS)

fclean	:	clean
			$(RM) $(LIBFT)/$(LIBFT).a
			$(RM) $(NAME)

re		:	fclean all

.PHONY	:	all bonus clean fclean re
