/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 04:41:01 by ykoh              #+#    #+#             */
/*   Updated: 2020/07/01 05:52:08 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static long double	ft_pow_pos(long double x, int y)
{
	if (y == 0)
		return (1);
	return (ft_pow_pos(x, y - 1) * x);
}

static long double	ft_pow_neg(long double x, int y)
{
	if (y == 0)
		return (1);
	return (ft_pow_neg(x, y + 1) / x);
}

long double			ft_pow(long double x, long double y)
{
	const int neg = (y < 0) ? 1 : 0;

	return ((neg) ? ft_pow_neg(x, y) : ft_pow_pos(x, y));
}
