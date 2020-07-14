/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 16:39:50 by ykoh              #+#    #+#             */
/*   Updated: 2020/07/13 22:55:42 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"

# include <stdarg.h>
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <wchar.h>

typedef struct	s_meta {
	char	minus;
	char	plus;
	char	space;
	char	hash;
	char	zero;
	char	flag;
	int		width;
	int		precision;
	char	*length;
	char	specifier;
}				t_meta;

typedef ssize_t	(*t_write)(int, const void *, size_t);

int				ft_printf(const char *restrict format, ...);

void			set_positional(char **str);
void			set_flag(char **str, t_meta *fs);
void			set_width(char **str, va_list ap, t_meta *fs);
void			set_precision(char **str, va_list ap, t_meta *fs);
void			set_length(char **str, t_meta *fs);

int				va_free(int argc, ...);

int				put_specifier_percent(va_list ap, t_meta *fs, long long *cnt);
int				put_specifier_c(va_list ap, t_meta *fs, long long *cnt);

int				put_specifier_n(va_list ap, t_meta *fs, long long *cnt);

int				put_specifier_s(va_list ap, t_meta *fs, long long *cnt);
int				put_specifier_di(va_list ap, t_meta *fs, long long *cnt);
int				put_specifier_u(va_list ap, t_meta *fs, long long *cnt);
int				put_specifier_x(va_list ap, t_meta *fs, long long *cnt);
int				put_specifier_p(va_list ap, t_meta *fs, long long *cnt);
int				put_specifier_efg(va_list ap, t_meta *fs, long long *cnt);
const char		*select_ret(va_list ap, t_meta *fs);

size_t			put_space_n(size_t n);
size_t			put_zero_n(size_t n);
ssize_t			without_write(int fildes, const void *buf, size_t nbyte);
int				put_sign(t_meta *fs, char *n);

int				put_wcstr(const wchar_t *s, ssize_t nbyte, t_meta *fs);
int				ft_wcsbyte(const wchar_t *s);

int				va_free(int argc, ...);
#endif
