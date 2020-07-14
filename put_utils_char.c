/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_utils_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 14:45:53 by ykoh              #+#    #+#             */
/*   Updated: 2020/07/15 01:01:29 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t	without_write(int fildes, const void *buf, size_t nbyte)
{
	if (fildes != 1 || !buf)
		return (0);
	return (nbyte);
}

size_t	put_zero_n(size_t n)
{
	const size_t	cnt = n;

	if (n <= 0)
		return (0);
	while (n--)
		write(1, "0", 1);
	return (cnt);
}

size_t	put_space_n(size_t n)
{
	const size_t	cnt = n;

	if (n <= 0)
		return (0);
	while (n--)
		write(1, " ", 1);
	return (cnt);
}

int		put_sign(t_meta *fs, char *n)
{
	int			ret;
	t_write		f;

	f = (fs->minus) ? write : without_write;
	ret = 0;
	if (*n == '-')
		ret = f(1, "-", 1);
	else if (fs->plus)
		ret = f(1, "+", 1);
	else if (fs->space && !(ft_strnstr(n, "nan", 4)))
		ret = f(1, " ", 1);
	return (ret);
}

int		va_free(int argc, ...)
{
	int		i;
	va_list	ap;
	void	**p;

	va_start(ap, argc);
	i = 0;
	while (i < argc)
	{
		p = va_arg(ap, void **);
		free(*p);
		*p = NULL;
		i++;
	}
	va_end(ap);
	return (-1);
}
