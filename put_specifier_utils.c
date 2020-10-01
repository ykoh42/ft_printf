/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 04:18:00 by ykoh              #+#    #+#             */
/*   Updated: 2020/09/15 02:09:23 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	put_zero(t_fs fs)
{
	int	ret;

	ret = 0;
	if (fs.padding <= 0)
		return (ret);
	while (fs.padding--)
		ret += write(1, "0", 1);
	return (ret);
}

int	put_space(t_fs fs)
{
	int	ret;

	ret = 0;
	if (fs.padding <= 0)
		return (ret);
	while (fs.padding--)
		ret += write(1, " ", 1);
	return (ret);
}
