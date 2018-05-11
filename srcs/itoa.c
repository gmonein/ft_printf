/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <gmonein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 20:42:49 by gmonein           #+#    #+#             */
/*   Updated: 2018/03/06 14:31:23 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ultoa_buf(unsigned long nbr)
{
	static char		res[42];
	int				i;

	i = 40;
	res[41] = '\0';
	if (nbr == 0)
		return (STR_ZERO);
	if (nbr == ULONG_MAX)
		return (STR_ULLONG_MAX);
	while (nbr != 0)
	{
		res[i] = nbr % 10 + '0';
		i--;
		nbr /= 10;
	}
	i += 1;
	return (&res[i]);
}

char	*ltoa_buf(long long nbr, char *signe)
{
	static char		res[42];
	int				i;

	i = 40;
	res[41] = '\0';
	*signe = nbr < 0 && (nbr *= -1) ? '-' : '+';
	if (nbr == 0)
	{
		*signe = '+';
		return (STR_ZERO);
	}
	if (nbr == LLONG_MIN)
	{
		*signe = '-';
		return (STR_LLONG_MIN);
	}
	while (nbr != 0)
	{
		res[i] = nbr % 10 + '0';
		i--;
		nbr /= 10;
	}
	return (&res[i + 1]);
}

char	*ft_ltoa_hex(unsigned long long nbr, int size, int cap, int base)
{
	static char		res[42];
	int				i;

	i = 40;
	res[i + 1] = '\0';
	if (size == 0)
		size = -1;
	if (nbr == 0 || (nbr == 4294967296 && size == 8))
		return (STR_ZERO);
	if (nbr == ULONG_MAX && base == 8)
		return (STR_ULONG_MAX_8);
	while (nbr && (size || size == -1))
	{
		if (cap)
			res[i] = nbr % base > 9 ? nbr % base - 10 + 'A' : nbr % base + '0';
		else
			res[i] = nbr % base > 9 ? nbr % base - 10 + 'a' : nbr % base + '0';
		nbr /= base;
		size--;
		i--;
	}
	return (&res[i + 1]);
}
