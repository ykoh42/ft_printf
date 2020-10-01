/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hextoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 18:39:55 by ykoh              #+#    #+#             */
/*   Updated: 2020/08/17 17:59:27 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	get_width(unsigned long long n)
{
	size_t	width;

	width = (n == 0);
	while (n)
	{
		n /= 16;
		width++;
	}
	return (width);
}

char			*ft_hextoa(unsigned long long n, char specifier)
{
	char			*num;
	int				rem;
	size_t			i;
	const size_t	width = get_width(n);

	if (!(num = ft_calloc(width + 1, sizeof(char))))
		return (NULL);
	i = 0;
	while (i < width)
	{
		rem = n % 16;
		n = n / 16;
		if (specifier == 'x')
			num[i] = "0123456789abcdef"[rem];
		else
			num[i] = "0123456789ABCDEF"[rem];
		i++;
	}
	return (ft_strrev(num));
}
