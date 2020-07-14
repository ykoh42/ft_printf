/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwchar_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 17:13:57 by ykoh              #+#    #+#             */
/*   Updated: 2020/07/12 15:07:51 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	set_bits(wchar_t c, char *s, size_t nbyte)
{
	const wchar_t	bits[6] = {0x0, 0x3F000000, 0xFC0000, 0x3F000, 0xFC0, 0x3F};
	const size_t	shift[6] = {0, 24, 18, 12, 6, 0};
	size_t			i;

	i = 1;
	while (i < nbyte)
	{
		s[i] |= (c & bits[6 - nbyte + i]) >> shift[6 - nbyte + i];
		i++;
	}
}

static void	init_bits(wchar_t c, char *s, size_t *nbyte)
{
	ft_memset(s, 0x80, 6);
	if (c <= 0x7FF)
		*nbyte = 2;
	else if (c <= 0xFFFF)
		*nbyte = 3;
	else if (c <= 0x1FFFFF)
		*nbyte = 4;
	else if (c <= 0x3FFFFFF)
		*nbyte = 5;
	else
		*nbyte = 6;
	if (c <= 0x7FF)
		ft_memset(s, 0xC0, 1);
	else if (c <= 0xFFFF)
		ft_memset(s, 0xE0, 1);
	else if (c <= 0x1FFFFF)
		ft_memset(s, 0xF0, 1);
	else if (c <= 0x3FFFFFF)
		ft_memset(s, 0xF8, 1);
	else
		ft_memset(s, 0xFC, 1);
}

ssize_t		ft_putwchar_fd(wchar_t c, int fd)
{
	char	s[6];
	size_t	nbyte;

	if (c <= 0x7F)
		return (write(fd, &c, 1));
	init_bits(c, s, &nbyte);
	set_bits(c, s, nbyte);
	if (c <= 0x7FF)
		s[0] |= (c & 0x7C0) >> 6;
	else if (c <= 0xFFFF)
		s[0] |= (c & 0xF000) >> 12;
	else if (c <= 0x1FFFFF)
		s[0] |= (c & 0x1C0000) >> 18;
	else if (c <= 0x3FFFFFF)
		s[0] |= (c & 0x3000000) >> 24;
	else
		s[0] |= (c & 0x40000000) >> 30;
	return (write(fd, s, nbyte));
}
