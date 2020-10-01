/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 22:40:04 by ykoh              #+#    #+#             */
/*   Updated: 2020/09/15 02:10:44 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"

# include <stdarg.h>
# include <unistd.h>
# include <wchar.h>

typedef struct	s_num {
	char	*sign;
	char	*hash;
	char	*num;
}				t_num;

typedef struct	s_char {
	int		none;
	wint_t	l;
}				t_char;

typedef struct	s_str {
	char	*none;
	wchar_t	*l;
}				t_str;

typedef struct	s_format_specifier {
	char			minus;
	char			plus;
	char			space;
	char			hash;
	char			zero;
	int				width;
	int				precision;
	char			*length;
	char			specifier;
	int				padding;
	t_num			num;
	t_char			c;
	t_str			s;
}				t_fs;

int				ft_printf(const char *format, ...);
void			set_fs(const char **format, t_fs *fs, va_list ap);

void			manage_length(va_list ap, t_fs *fs, int nbyte);
void			manage_length_n(va_list ap, t_fs *fs, int nbyte);

void			manage_precision(t_fs *fs);
void			manage_flags(t_fs *fs);
void			manage_width(t_fs *fs);

int				put_specifier_diuxp(t_fs fs);
int				put_specifier_efg(t_fs fs);
int				put_specifier_c(t_fs fs);
int				put_specifier_s(t_fs fs);
int				put_specifier_percent(t_fs fs);

int				put_space(t_fs fs);
int				put_zero(t_fs fs);

int				get_wchar_byte(wchar_t c);
int				ft_wcsbyte(const wchar_t *s);

#endif
