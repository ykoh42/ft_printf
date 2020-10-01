/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 18:39:55 by ykoh              #+#    #+#             */
/*   Updated: 2020/08/17 17:35:28 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	get_width(unsigned long long n)
{
	size_t	width;

	width = (n == 0);
	while (n)
	{
		n /= 10;
		width++;
	}
	return (width);
}

char			*ft_utoa(unsigned long long n)
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
		rem = n % 10;
		n = n / 10;
		num[i] = "0123456789"[rem];
		i++;
	}
	return (ft_strrev(num));
}
