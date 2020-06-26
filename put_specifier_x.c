/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_specifier_x.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 17:29:16 by ykoh              #+#    #+#             */
/*   Updated: 2020/06/25 14:45:27 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	put_x(t_meta *fs, char *x)
{
	t_func			f;
	int				ret;
	const size_t	x_len = ft_strlen(x);

	f = (fs->minus) ? write : without_write;
	ret = 0;
	if (fs->precision != -1 && (size_t)fs->precision > x_len)
		ret = (fs->minus) ?
				put_zero_n(fs->precision - x_len) : fs->precision - x_len;
	ret += f(1, x, x_len);
	return (ret);
}

static int	put_hash_flag(t_meta *fs)
{
	int		ret;

	if (!fs->hash)
		return (0);
	if (fs->specifier == 'x')
		ret = write(1, "0x", 2);
	else
		ret = write(1, "0X", 2);
	return (ret);
}

static void	*type_new_x(va_list ap, t_meta *fs)
{
	if (fs->length != NULL && ft_strncmp(fs->length, "ll", 2) == 0)
		return (ft_hextoa(va_arg(ap, unsigned long long int), fs->specifier));
	else if (fs->length != NULL && ft_strncmp(fs->length, "l", 2) == 0)
		return (ft_hextoa(va_arg(ap, unsigned long int), fs->specifier));
	else
		return (ft_hextoa(va_arg(ap, unsigned int), fs->specifier));
}

int			put_specifier_x(va_list ap, t_meta *fs, long long *cnt)
{
	char	*x;
	int		width_cnt;

	if (!(x = type_new_x(ap, fs)))
		return (-1);
	if (fs->minus)
	{
		width_cnt = put_hash_flag(fs) + put_x(fs, x);
		if (fs->width && fs->width > width_cnt)
			*cnt += put_space_n(fs->width - width_cnt);
		*cnt += width_cnt;
	}
	else
	{
		width_cnt = (fs->hash) ? 2 + put_x(fs, x) : put_x(fs, x);
		if (fs->width && fs->width > width_cnt && fs->precision != -1)
			*cnt += put_space_n(fs->width - width_cnt);
		*cnt += (fs->hash) ? put_hash_flag(fs) : 0;
		if (fs->zero && fs->precision == -1)
			*cnt += put_zero_n(fs->width - width_cnt);
		fs->minus = '-';
		*cnt += put_x(fs, x);
	}
	free(x);
	return (*cnt);
}
