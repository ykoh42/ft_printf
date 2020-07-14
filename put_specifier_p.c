/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_specifier_p.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 17:29:16 by ykoh              #+#    #+#             */
/*   Updated: 2020/07/12 15:31:26 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	put_p(t_meta *fs, char *p)
{
	t_write			f;
	int				ret;
	const size_t	p_len = ft_strlen(p);

	if (fs->precision == 0 && *p == '0')
		return (fs->precision);
	f = (fs->minus) ? write : without_write;
	ret = 0;
	if (fs->precision != -1 && (size_t)fs->precision > p_len)
		ret = (fs->minus) ?
			put_zero_n(fs->precision - p_len) : fs->precision - p_len;
	ret += f(1, p, p_len);
	return (ret);
}

int			put_specifier_p(va_list ap, t_meta *fs, long long *cnt)
{
	char	*p;
	int		width_cnt;

	if (!(p = ft_hextoa((uintptr_t)va_arg(ap, void *), 'x')))
		return (-1);
	if (fs->minus)
	{
		width_cnt = write(1, "0x", 2) + put_p(fs, p);
		if (fs->width && fs->width > width_cnt)
			*cnt += put_space_n(fs->width - width_cnt);
		*cnt += width_cnt;
	}
	else
	{
		width_cnt = 2 + put_p(fs, p);
		if (fs->width && fs->width > width_cnt)
			*cnt += put_space_n(fs->width - width_cnt);
		fs->minus = '-';
		*cnt += write(1, "0x", 2) + put_p(fs, p);
	}
	free(p);
	return (*cnt);
}
