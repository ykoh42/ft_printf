/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnegzero.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 04:43:19 by ykoh              #+#    #+#             */
/*   Updated: 2020/07/11 22:10:50 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isneg_dbl(double x)
{
	const long long x_ll = *((long long *)(&x));
	const long long sign = 1LL << 63;

	if ((sign & x_ll) == sign)
		return (1);
	return (0);
}
