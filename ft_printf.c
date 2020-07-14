/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 15:31:14 by ykoh              #+#    #+#             */
/*   Updated: 2020/07/13 00:24:58 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	put_specifier(va_list ap, t_meta *fs, long long *cnt)
{
	if (fs->specifier == 'p')
		return (put_specifier_p(ap, fs, cnt));
	else if (fs->specifier == 'x' || fs->specifier == 'X')
		return (put_specifier_x(ap, fs, cnt));
	else if (fs->specifier == '%')
		return (put_specifier_percent(ap, fs, cnt));
	else if (fs->specifier == 'd' || fs->specifier == 'i')
		return (put_specifier_di(ap, fs, cnt));
	else if (fs->specifier == 'c')
		return (put_specifier_c(ap, fs, cnt));
	else if (fs->specifier == 'n')
		return (put_specifier_n(ap, fs, cnt));
	else if (fs->specifier == 's')
		return (put_specifier_s(ap, fs, cnt));
	else if (fs->specifier == 'u')
		return (put_specifier_u(ap, fs, cnt));
	else if (fs->specifier == 'e' || fs->specifier == 'f' ||
			fs->specifier == 'g')
		return (put_specifier_efg(ap, fs, cnt));
	return (-1);
}

static int	set_meta(char *str, va_list ap, t_meta *fs)
{
	const char	*p = str;

	if (!str)
		return (va_free(1, &p));
	str++;
	while (*str)
	{
		if (!ft_strchr("$-+ #0*0123456789.lhnfgecspdiuxX%", *str))
			return (va_free(1, &p));
		str++;
	}
	str = (char *)p + 1;
	set_positional(&str);
	set_flag(&str, fs);
	set_width(&str, ap, fs);
	set_precision(&str, ap, fs);
	set_length(&str, fs);
	free((char *)p);
	return (1);
}

static int	put_format(const char *restrict *format, va_list ap, long long *cnt)
{
	const char *const	p = (*format)++;
	t_meta				*fs;
	int					ret;

	while (**format && !ft_strchr("nfgecspdiuxX%", **format))
		(*format)++;
	if (!(fs = ft_calloc(1, sizeof(t_meta))))
		return (-1);
	if (**format)
		fs->specifier = **format;
	else
		return (va_free(1, &fs));
	if (!set_meta(ft_strndup(p, *format - p + 1), ap, fs))
		return (va_free(1, &fs));
	if ((ret = put_specifier(ap, fs, cnt)) == -1)
		return (va_free(1, &fs));
	free(fs);
	return (ret);
}

int			ft_printf(const char *restrict format, ...)
{
	va_list		ap;
	long long	cnt;

	cnt = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format != '%')
			cnt += write(1, format, 1);
		else if (put_format(&format, ap, &cnt) < 0)
			return (-1);
		format++;
	}
	va_end(ap);
	return ((int)cnt);
}
