/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_specifier_x.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 17:29:16 by ykoh              #+#    #+#             */
/*   Updated: 2020/07/12 18:44:25 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	put_x(t_meta *fs, char *x)
{
	t_write			f;
	int				ret;
	const size_t	x_len = ft_strlen(x);

	if (fs->precision == 0 && *x == '0')
		return (fs->precision);
	f = (fs->minus) ? write : without_write;
	ret = 0;
	if (fs->precision != -1 && (size_t)fs->precision > x_len)
		ret = (fs->minus) ?
				put_zero_n(fs->precision - x_len) : fs->precision - x_len;
	ret += f(1, x, x_len);
	return (ret);
}

static int	put_hash_flag(t_meta *fs, char *x)
{
	int		ret;

	if (!fs->hash || *x == '0')
		return (0);
	if (fs->specifier == 'x')
		ret = write(1, "0x", 2);
	else
		ret = write(1, "0X", 2);
	return (ret);
}

static void	put_specifier_x_process(t_meta *fs, long long *cnt, char *x)
{
	int		width_cnt;

	if (fs->minus)
	{
		width_cnt = put_hash_flag(fs, x) + put_x(fs, x);
		if (fs->width && fs->width > width_cnt)
			*cnt += put_space_n(fs->width - width_cnt);
		*cnt += width_cnt;
	}
	else
	{
		width_cnt = (fs->hash && *x != '0') ? 2 + put_x(fs, x) : put_x(fs, x);
		fs->minus = '-';
		if (fs->width && fs->width > width_cnt)
			*cnt += (fs->zero && fs->precision == -1) ?
				put_hash_flag(fs, x) + put_zero_n(fs->width - width_cnt) :
				put_space_n(fs->width - width_cnt) + put_hash_flag(fs, x);
		else
			*cnt += put_hash_flag(fs, x);
		*cnt += put_x(fs, x);
	}
}

static void	*type_new_x(va_list ap, t_meta *fs)
{
	if (fs->length != NULL && ft_strncmp(fs->length, "ll", 2) == 0)
		return (ft_hextoa(va_arg(ap, unsigned long long int), fs->specifier));
	else if (fs->length != NULL && ft_strncmp(fs->length, "l", 2) == 0)
		return (ft_hextoa(va_arg(ap, unsigned long int), fs->specifier));
	else if (fs->length != NULL && ft_strncmp(fs->length, "hh", 2) == 0)
		return (ft_hextoa((unsigned char)va_arg(ap, unsigned int),
				fs->specifier));
	else if (fs->length != NULL && ft_strncmp(fs->length, "h", 2) == 0)
		return (ft_hextoa((unsigned short int)va_arg(ap, unsigned int),
				fs->specifier));
	else
		return (ft_hextoa(va_arg(ap, unsigned int), fs->specifier));
}

int			put_specifier_x(va_list ap, t_meta *fs, long long *cnt)
{
	char	*x;

	if (!(x = type_new_x(ap, fs)))
		return (-1);
	put_specifier_x_process(fs, cnt, x);
	free(x);
	return (*cnt);
}
