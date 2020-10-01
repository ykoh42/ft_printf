/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_length.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 23:03:27 by ykoh              #+#    #+#             */
/*   Updated: 2020/09/30 17:59:16 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	set_sign(t_fs *fs, char *ret)
{
	if (*ret == '-')
	{
		fs->num.sign = "-";
		fs->num.num = ft_strdup(ret + 1);
	}
	else
	{
		fs->num.sign = "";
		fs->num.num = ft_strdup(ret);
	}
	free(ret);
}

static void	manage_length_cs(va_list ap, t_fs *fs)
{
	if (fs->specifier == 's')
	{
		if (fs->length && ft_strncmp(fs->length, "l", 2) == 0)
		{
			if (!(fs->s.l = va_arg(ap, wchar_t *)))
				fs->s.l = L"(null)";
		}
		else
		{
			if (!(fs->s.none = va_arg(ap, char *)))
				fs->s.none = "(null)";
		}
	}
	else if (fs->specifier == 'c')
	{
		if (fs->length && ft_strncmp(fs->length, "l", 2) == 0)
			fs->c.l = va_arg(ap, wint_t);
		else
			fs->c.none = va_arg(ap, int);
	}
}

static void	manage_length_uox(va_list ap, t_fs *fs)
{
	unsigned long long	n;

	if (fs->length && ft_strncmp(fs->length, "ll", 2) == 0)
		n = va_arg(ap, unsigned long long int);
	else if (fs->length && ft_strncmp(fs->length, "l", 2) == 0)
		n = va_arg(ap, unsigned long int);
	else if (fs->length && ft_strncmp(fs->length, "h", 2) == 0)
		n = (unsigned short int)va_arg(ap, int);
	else if (fs->length && ft_strncmp(fs->length, "hh", 2) == 0)
		n = (unsigned char)va_arg(ap, int);
	else
		n = va_arg(ap, unsigned int);
	if (fs->specifier == 'u')
		fs->num.num = ft_utoa(n);
	else if (fs->specifier == 'o')
		fs->num.num = ft_octtoa(n);
	else
		fs->num.num = ft_hextoa(n, fs->specifier);
}

static void	manage_length_di(va_list ap, t_fs *fs)
{
	long long	n;

	if (fs->length && ft_strncmp(fs->length, "ll", 2) == 0)
		n = va_arg(ap, long long int);
	else if (fs->length && ft_strncmp(fs->length, "l", 2) == 0)
		n = va_arg(ap, long int);
	else if (fs->length && ft_strncmp(fs->length, "h", 2) == 0)
		n = (short int)va_arg(ap, int);
	else if (fs->length && ft_strncmp(fs->length, "hh", 2) == 0)
		n = (signed char)va_arg(ap, int);
	else
		n = va_arg(ap, int);
	fs->num.num = ft_itoa(n);
	set_sign(fs, fs->num.num);
}

void		manage_length(va_list ap, t_fs *fs, int nbyte)
{
	if (fs->specifier == 'd' || fs->specifier == 'i')
		manage_length_di(ap, fs);
	else if (fs->specifier == 'u' || fs->specifier == 'o' ||
			fs->specifier == 'x' || fs->specifier == 'X')
		manage_length_uox(ap, fs);
	else if (fs->specifier == 'p')
	{
		fs->num.num = ft_hextoa((uintptr_t)va_arg(ap, void *), 'x');
		fs->hash = '#';
	}
	else if (fs->specifier == 'c' || fs->specifier == 's')
		manage_length_cs(ap, fs);
	else if (fs->specifier == 'n')
		manage_length_n(ap, fs, nbyte);
	else if (fs->specifier == 'e' || fs->specifier == 'f' ||
			fs->specifier == 'g')
	{
		fs->num.num = ft_dtoa(va_arg(ap, double), fs->precision, fs->specifier);
		set_sign(fs, fs->num.num);
	}
}
