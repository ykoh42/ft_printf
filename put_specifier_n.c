/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_specifier_n.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 17:29:16 by ykoh              #+#    #+#             */
/*   Updated: 2020/06/24 06:03:44 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		type_new_n_with_length(va_list ap, char *length, long long *cnt)
{
	void	*n;

	if (length != NULL && ft_strncmp(length, "ll", 2) == 0)
	{
		n = va_arg(ap, long long int *);
		*((long long int *)n) = *cnt;
	}
	else if (length != NULL && ft_strncmp(length, "l", 2) == 0)
	{
		n = va_arg(ap, long int *);
		*((long int *)n) = *cnt;
	}
	else if (length != NULL && ft_strncmp(length, "hh", 2) == 0)
	{
		n = va_arg(ap, signed char *);
		*((signed char *)n) = *cnt;
	}
	else if (length != NULL && ft_strncmp(length, "h", 2) == 0)
	{
		n = va_arg(ap, short int *);
		*((short int *)n) = *cnt;
	}
}

void		type_new_n(va_list ap, char *length, long long *cnt)
{
	void	*n;

	if (length)
		type_new_n_with_length(ap, length, cnt);
	else
	{
		n = va_arg(ap, int *);
		*((int *)n) = *cnt;
	}
}

int			put_specifier_n(va_list ap, t_meta *fs, long long *cnt)
{
	type_new_n(ap, fs->length, cnt);
	return (*cnt);
}
