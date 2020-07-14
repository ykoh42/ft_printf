/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isinf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 04:43:19 by ykoh              #+#    #+#             */
/*   Updated: 2020/07/01 04:43:25 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isinf(double x)
{
	const long long x_ll = *((long long *)(&x));
	const long long sign = 1LL << 63;
	const long long exponent = 2047LL << 52;

	if (x_ll == (sign | exponent) || x_ll == exponent)
		return (1);
	return (0);
}
