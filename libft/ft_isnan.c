/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnan.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 04:42:52 by ykoh              #+#    #+#             */
/*   Updated: 2020/07/01 04:43:04 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isnan(double x)
{
	const long long	x_ll = *((long long *)(&x));
	const long long	exponent = 2047LL << 52;
	const long long	mantissa = 4503599627370495LL;

	if (((x_ll & exponent) == exponent) && ((x_ll & mantissa) != 0LL))
		return (1);
	return (0);
}
