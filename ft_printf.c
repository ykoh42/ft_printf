/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 14:52:43 by ykoh              #+#    #+#             */
/*   Updated: 2020/06/11 15:05:25 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char * restrict format, ...)
{
	va_list	ap;
	int		cnt;

	va_start(ap, format);




	va_end(ap);
	return (cnt);
}
