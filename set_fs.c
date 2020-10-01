/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 22:49:17 by ykoh              #+#    #+#             */
/*   Updated: 2020/09/15 00:20:51 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	set_flags(const char **format, t_fs *fs)
{
	while (**format == '-' || **format == '+' || **format == ' ' ||
			**format == '#' || **format == '0')
	{
		if (**format == '-')
			fs->minus = '-';
		if (**format == '+')
			fs->plus = '+';
		if (**format == ' ')
			fs->space = ' ';
		if (**format == '#')
			fs->hash = '#';
		if (**format == '0')
			fs->zero = '0';
		(*format)++;
	}
	if (fs->space && fs->plus)
		fs->space = 0;
	if (fs->zero && fs->minus)
		fs->zero = 0;
}

static void	set_width(const char **format, t_fs *fs, va_list ap)
{
	if (**format == '*')
	{
		fs->width = va_arg(ap, int);
		(*format)++;
	}
	else if (ft_isdigit(**format))
	{
		fs->width = ft_atoi(*format);
		while (ft_isdigit(**format))
			(*format)++;
	}
	if (fs->width < 0)
	{
		fs->minus = '-';
		fs->width = -fs->width;
	}
}

static void	set_precision(const char **format, t_fs *fs, va_list ap)
{
	if (**format == '.')
	{
		(*format)++;
		if (**format == '*')
		{
			fs->precision = va_arg(ap, int);
			(*format)++;
		}
		else if (ft_isdigit(**format))
		{
			fs->precision = ft_atoi(*format);
			while (ft_isdigit(**format))
				(*format)++;
		}
		if (fs->precision < 0)
			fs->precision = -1;
	}
	else
		fs->precision = -1;
}

static void	set_length(const char **format, t_fs *fs)
{
	if (ft_strncmp(*format, "hh", 2) == 0)
	{
		fs->length = "hh";
		(*format) += 2;
	}
	else if (**format == 'h')
	{
		fs->length = "h";
		(*format) += 1;
	}
	if (ft_strncmp(*format, "ll", 2) == 0)
	{
		fs->length = "ll";
		(*format) += 2;
	}
	else if (**format == 'l')
	{
		fs->length = "l";
		(*format) += 1;
	}
}

void		set_fs(const char **format, t_fs *fs, va_list ap)
{
	set_flags(format, fs);
	set_width(format, fs, ap);
	set_precision(format, fs, ap);
	set_length(format, fs);
	fs->specifier = **format;
	if (fs->specifier)
		(*format)++;
	fs->num.sign = "";
	fs->num.hash = "";
	fs->num.num = "";
}
