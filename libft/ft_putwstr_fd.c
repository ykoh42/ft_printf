/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwstr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 18:01:22 by ykoh              #+#    #+#             */
/*   Updated: 2020/07/11 23:04:45 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_putwstr_fd(wchar_t *s, int fd)
{
	int	ret;

	ret = 0;
	if (!s)
		return (-1);
	while (*s)
		ret += ft_putwchar_fd(*s++, fd);
	return (ret);
}
