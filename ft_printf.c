/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 22:20:29 by ykoh              #+#    #+#             */
/*   Updated: 2020/09/30 17:56:59 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	put_specifier(t_fs fs)
{
	if (fs.specifier == 'd' || fs.specifier == 'i' || fs.specifier == 'u' ||
		fs.specifier == 'o' || fs.specifier == 'x' || fs.specifier == 'X' ||
		fs.specifier == 'p')
		return (put_specifier_diuxp(fs));
	else if (fs.specifier == 'e' || fs.specifier == 'f' || fs.specifier == 'g')
		return (put_specifier_efg(fs));
	else if (fs.specifier == 'c')
		return (put_specifier_c(fs));
	else if (fs.specifier == 's')
		return (put_specifier_s(fs));
	else if (fs.specifier == '%')
		return (put_specifier_percent(fs));
	else
		return (0);
}

static void	fs_manager(va_list ap, t_fs *fs, int nbyte)
{
	manage_length(ap, fs, nbyte);
	manage_precision(fs);
	manage_flags(fs);
	manage_width(fs);
}

static int	write_format(const char **format, va_list ap, int nbyte)
{
	t_fs	fs;

	ft_bzero(&fs, sizeof(fs));
	(*format)++;
	set_fs(format, &fs, ap);
	fs_manager(ap, &fs, nbyte);
	return (put_specifier(fs));
}

int			ft_printf(const char *format, ...)
{
	va_list	ap;
	int		nbyte;

	nbyte = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format != '%')
			nbyte += write(1, format++, 1);
		else
			nbyte += write_format(&format, ap, nbyte);
	}
	va_end(ap);
	return (nbyte);
}
