/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 16:39:50 by ykoh              #+#    #+#             */
/*   Updated: 2020/06/21 14:39:41 by ykoh             ###   ########.fr       */
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

int				ft_printf(const char *restrict format, ...);

int				put_conversion(const char *restrict *format, va_list ap, long long *cnt);
void			parse_format(const char *restrict *format, va_list ap,
							t_meta *fs);
void			set_meta(const char *restrict *format, va_list ap, t_meta *fs);
int				put_format(va_list ap, t_meta *fs, long long *cnt);


void			set_flag(const char *restrict *format, t_meta *fs);
void			set_width(const char *restrict *format, va_list ap, t_meta *fs);
void			set_precision(const char *restrict *format, va_list ap, t_meta *fs);
void			set_length(const char *restrict *format, t_meta *fs);
void			set_specifier(const char *restrict *format, t_meta *fs);


int				put_specifier_percent(va_list ap, t_meta *fs, long long *cnt);

int				put_specifier_c(va_list ap, t_meta *fs, long long *cnt);
void			*type_new_c(va_list ap, char *length);

int				put_specifier_n(va_list ap, t_meta *fs, long long *cnt);
void			type_new_n(va_list ap, char *length, long long *cnt);
void			type_new_n_with_length(va_list ap, char *length, long long *cnt);

int				put_specifier_s(va_list ap, t_meta *fs, long long *cnt);


size_t			put_space_n(size_t n);
size_t			put_zero_n(size_t n);

#endif
