#include "ft_printf.h"

size_t	put_zero_n(size_t n)
{
	const size_t	cnt = n;

	if (n <= 0)
		return (0);
	while (n--)
		write(1, "0", 1);
	return (cnt);
}

size_t	put_space_n(size_t n)
{
	const size_t	cnt = n;

	if (n <= 0)
		return (0);
	while (n--)
		write(1, " ", 1);
	return (cnt);
}
