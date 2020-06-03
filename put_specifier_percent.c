/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_specifier_percent.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 17:12:41 by ykoh              #+#    #+#             */
/*   Updated: 2020/06/21 17:12:42 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		put_specifier_percent(va_list ap, t_meta *fs, long long *cnt)
{
	va_list	tmp;

	va_copy(tmp, ap);
	if (fs->specifier != '%')
		return (-1);
	*cnt += write(1, "%", 1);
	return (1);
}
