/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 15:31:14 by ykoh              #+#    #+#             */
/*   Updated: 2020/06/21 14:26:24 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *restrict format, ...)
{
	va_list		ap;
	long long	cnt;

	cnt = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format != '%')
		{
			cnt += write(1, format, 1);
		}
		else
		{
			if (put_conversion(&format, ap, &cnt) < 0)
				return (-1);
		}
		format++;
	}
	va_end(ap);
	return ((int)cnt);
}
