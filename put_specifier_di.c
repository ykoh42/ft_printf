/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_specifier_di.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 04:50:00 by ykoh              #+#    #+#             */
/*   Updated: 2020/07/13 02:09:42 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	put_di(t_meta *fs, char *di)
{
	t_write	f;
	int		ret;
	size_t	di_len;

	if (fs->precision == 0 && *di == '0')
		return (0);
	if (*di == '-')
		di++;
	di_len = ft_strlen(di);
	f = (fs->minus) ? write : without_write;
	ret = 0;
	if (fs->precision != -1 && (size_t)fs->precision > di_len)
		ret = (fs->minus) ?
			put_zero_n(fs->precision - di_len) : fs->precision - di_len;
	ret += f(1, di, di_len);
	return (ret);
}

static char	*type_new_di(va_list ap, char *length)
{
	if (length != NULL && ft_strncmp(length, "ll", 2) == 0)
		return (ft_lltoa((long long int)va_arg(ap, long long int)));
	else if (length != NULL && ft_strncmp(length, "l", 2) == 0)
		return (ft_lltoa((long int)va_arg(ap, long int)));
	else if (length != NULL && ft_strncmp(length, "hh", 2) == 0)
		return (ft_lltoa((signed char)va_arg(ap, int)));
	else if (length != NULL && ft_strncmp(length, "h", 2) == 0)
		return (ft_lltoa((short int)va_arg(ap, int)));
	else
		return (ft_lltoa((int)va_arg(ap, int)));
}

int			put_specifier_di(va_list ap, t_meta *fs, long long *cnt)
{
	int		sign_plus_di;
	char	*di;

	if (!(di = type_new_di(ap, fs->length)))
		return (-1);
	sign_plus_di = put_sign(fs, di) + put_di(fs, di);
	if (fs->minus)
	{
		if (fs->width && fs->width > sign_plus_di)
			*cnt += put_space_n(fs->width - sign_plus_di);
		*cnt += sign_plus_di;
	}
	else
	{
		fs->minus = '-';
		if (fs->width && fs->width > sign_plus_di)
			*cnt += (fs->zero && fs->precision == -1) ?
				put_sign(fs, di) + put_zero_n(fs->width - sign_plus_di) :
				put_space_n(fs->width - sign_plus_di) + put_sign(fs, di);
		else
			*cnt += put_sign(fs, di);
		*cnt += put_di(fs, di);
	}
	free(di);
	return (*cnt);
}
