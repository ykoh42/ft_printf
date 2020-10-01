/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_specifier.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 23:03:27 by ykoh              #+#    #+#             */
/*   Updated: 2020/09/15 02:24:52 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		put_specifier_percent(t_fs fs)
{
	int	ret;

	ret = 0;
	if (fs.minus)
		ret += (write(1, "%", 1) + put_space(fs));
	else
	{
		ret += (fs.zero) ? put_zero(fs) : put_space(fs);
		ret += write(1, "%", 1);
	}
	return (ret);
}

int		put_specifier_c(t_fs fs)
{
	int	ret;

	ret = 0;
	if (fs.minus)
	{
		ret += (fs.c.none) ?
				write(1, &fs.c.none, 1) : ft_putwchar_fd(fs.c.l, 1);
		ret += put_space(fs);
	}
	else
	{
		ret += put_space(fs);
		ret += (fs.c.none) ?
				write(1, &fs.c.none, 1) : ft_putwchar_fd(fs.c.l, 1);
	}
	return (ret);
}

int		put_specifier_efg(t_fs fs)
{
	int	ret;

	ret = 0;
	if (fs.minus)
	{
		ret += (write(1, fs.num.sign, ft_strlen(fs.num.sign))
			+ write(1, fs.num.num, ft_strlen(fs.num.num)) + put_space(fs));
	}
	else
	{
		if (!fs.zero || ft_strncmp(fs.num.num, "nan", 3) == 0 ||
						ft_strncmp(fs.num.num, "inf", 3) == 0)
			ret += put_space(fs);
		ret += write(1, fs.num.sign, ft_strlen(fs.num.sign));
		if (fs.zero && ft_strncmp(fs.num.num, "nan", 3) != 0 &&
						ft_strncmp(fs.num.num, "inf", 3) != 0)
			ret += put_zero(fs);
		ret += write(1, fs.num.num, ft_strlen(fs.num.num));
	}
	free(fs.num.num);
	return (ret);
}

int		put_specifier_diuxp(t_fs fs)
{
	int	ret;

	ret = 0;
	if (fs.minus)
	{
		ret += (write(1, fs.num.sign, ft_strlen(fs.num.sign))
			+ write(1, fs.num.hash, ft_strlen(fs.num.hash))
			+ write(1, fs.num.num, ft_strlen(fs.num.num)) + put_space(fs));
	}
	else
	{
		if (!fs.zero || fs.precision != -1)
			ret += put_space(fs);
		ret += (write(1, fs.num.sign, ft_strlen(fs.num.sign))
			+ write(1, fs.num.hash, ft_strlen(fs.num.hash)));
		if (fs.zero && fs.precision == -1)
			ret += put_zero(fs);
		ret += write(1, fs.num.num, ft_strlen(fs.num.num));
	}
	free(fs.num.num);
	return (ret);
}
