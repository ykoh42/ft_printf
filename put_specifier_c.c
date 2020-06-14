/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_specifier_c.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 17:29:40 by ykoh              #+#    #+#             */
/*   Updated: 2020/06/22 17:26:20 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		*type_new_c(va_list ap, char *length)
{
	void	*c;

	if (length != NULL && ft_strncmp(length, "l", 2) == 0)
	{
		c = ft_calloc(1, sizeof(wint_t));
		*((wint_t *)c) = va_arg(ap, wint_t);
	}
	else
	{
		c = ft_calloc(1, sizeof(int));
		*((int *)c) = va_arg(ap, int);
	}
	return (c);
}

int			put_specifier_c(va_list ap, t_meta *fs, long long *cnt)
{
	void	*c;

	if (!(c = type_new_c(ap, fs->length)))
		return (-1);
	if (fs->minus)
	{
		*cnt += write(1, c, 1);
		if (fs->width)
			*cnt += put_space_n(fs->width - 1);
	}
	else
	{
		if (fs->width)
			*cnt += put_space_n(fs->width - 1);
		*cnt += write(1, c, 1);
	}
	free(c);
	return (*cnt);
}
