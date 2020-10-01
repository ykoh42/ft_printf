/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_length_n.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 17:29:16 by ykoh              #+#    #+#             */
/*   Updated: 2020/09/04 00:53:42 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	manage_length_n_ll(va_list ap, int nbyte)
{
	long long int	*n;

	n = (long long int *)va_arg(ap, long long int *);
	*n = nbyte;
}

static void	manage_length_n_l(va_list ap, int nbyte)
{
	long int	*n;

	n = (long int *)va_arg(ap, long int *);
	*n = nbyte;
}

static void	manage_length_n_h(va_list ap, int nbyte)
{
	short int	*n;

	n = (short int *)va_arg(ap, short int *);
	*n = nbyte;
}

static void	manage_length_n_hh(va_list ap, int nbyte)
{
	signed char	*n;

	n = (signed char *)va_arg(ap, signed char *);
	*n = nbyte;
}

void		manage_length_n(va_list ap, t_fs *fs, int nbyte)
{
	int	*n;

	if (fs->length && ft_strncmp(fs->length, "ll", 2) == 0)
		manage_length_n_ll(ap, nbyte);
	else if (fs->length && ft_strncmp(fs->length, "l", 2) == 0)
		manage_length_n_l(ap, nbyte);
	else if (fs->length && ft_strncmp(fs->length, "h", 2) == 0)
		manage_length_n_h(ap, nbyte);
	else if (fs->length && ft_strncmp(fs->length, "hh", 2) == 0)
		manage_length_n_hh(ap, nbyte);
	else
	{
		n = (int *)va_arg(ap, int *);
		*n = nbyte;
	}
}
