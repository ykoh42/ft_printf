/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_specifier_percent.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 17:12:41 by ykoh              #+#    #+#             */
/*   Updated: 2020/07/12 16:51:29 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		put_specifier_percent(va_list ap, t_meta *fs, long long *cnt)
{
	va_list	tmp;
	int		width_cnt;

	va_copy(tmp, ap);
	if (fs->specifier != '%')
		return (-1);
	if (fs->minus)
	{
		width_cnt = write(1, "%", 1);
		if (fs->width && fs->width > width_cnt)
			*cnt += put_space_n(fs->width - width_cnt);
		*cnt += width_cnt;
	}
	else
	{
		width_cnt = 1;
		if (fs->width && fs->width > width_cnt)
			*cnt += (fs->zero) ?
				put_zero_n(fs->width - 1) : put_space_n(fs->width - 1);
		*cnt += write(1, "%", 1);
	}
	return (*cnt);
}
