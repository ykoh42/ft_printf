/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_specifier_s.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 16:30:28 by ykoh              #+#    #+#             */
/*   Updated: 2020/07/13 22:47:51 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	length_l(va_list ap, t_meta *fs, long long *cnt)
{
	const wchar_t	*s = va_arg(ap, wchar_t *);
	int				width_cnt;

	if (s == NULL)
		s = L"(null)";
	if (fs->minus)
	{
		width_cnt = (fs->precision == -1 || fs->precision > ft_wcsbyte(s)) ?
			put_wcstr(s, ft_wcsbyte(s), fs) : put_wcstr(s, fs->precision, fs);
		if (fs->width && fs->width > width_cnt)
			*cnt += put_space_n(fs->width - width_cnt);
		*cnt += width_cnt;
	}
	else
	{
		width_cnt = (fs->precision == -1 || fs->precision > ft_wcsbyte(s)) ?
			put_wcstr(s, ft_wcsbyte(s), fs) : put_wcstr(s, fs->precision, fs);
		if (fs->width && fs->width > width_cnt)
			*cnt += (fs->zero && fs->precision == -1) ?
		put_zero_n(fs->width - width_cnt) : put_space_n(fs->width - width_cnt);
		fs->minus = '-';
		*cnt += put_wcstr(s, width_cnt, fs);
	}
	return (*cnt);
}

static int	length_none(va_list ap, t_meta *fs, long long *cnt)
{
	const char	*s = va_arg(ap, char *);
	int			width_cnt;

	if (s == NULL)
		s = "(null)";
	if (fs->minus)
	{
		width_cnt = (fs->precision == -1 || fs->precision > (int)ft_strlen(s)) ?
				write(1, s, ft_strlen(s)) : write(1, s, fs->precision);
		if (fs->width && fs->width > width_cnt)
			*cnt += put_space_n(fs->width - width_cnt);
		*cnt += width_cnt;
	}
	else
	{
		width_cnt = (fs->precision == -1 || fs->precision > (int)ft_strlen(s)) ?
				ft_strlen(s) : fs->precision;
		if (fs->width && fs->width > width_cnt)
			*cnt += (fs->zero && fs->precision == -1) ?
		put_zero_n(fs->width - width_cnt) : put_space_n(fs->width - width_cnt);
		*cnt += write(1, s, width_cnt);
	}
	return (*cnt);
}

int			put_specifier_s(va_list ap, t_meta *fs, long long *cnt)
{
	if (fs->length != NULL && ft_strncmp(fs->length, "l", 2) == 0)
		return (length_l(ap, fs, cnt));
	else
		return (length_none(ap, fs, cnt));
}
