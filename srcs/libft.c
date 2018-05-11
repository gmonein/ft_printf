/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <gmonein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 20:42:49 by gmonein           #+#    #+#             */
/*   Updated: 2018/03/06 14:31:23 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_strlen(const char *str)
{
	size_t		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strcpy(char *dest, const char *src)
{
	int		i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strncpy(char *dst, char *src, size_t n)
{
	size_t		i;
	size_t		j;

	j = n;
	while (j--)
		((unsigned char *)dst)[j] = '\0';
	i = 0;
	while (n-- && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}

void	*ft_bzero(void *ptr, size_t num)
{
	unsigned char	*fresh;
	int				value;

	value = 0;
	fresh = (unsigned char *)ptr;
	while (num)
	{
		*fresh = (unsigned char)value;
		num--;
		if (num)
			fresh++;
	}
	return (ptr);
}

int		ft_atoi(const char *str)
{
	int		res;
	int		sign;

	res = 0;
	sign = *str == '-' ? -1 : 1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res *= 10;
		res += *str - '0';
		str++;
	}
	return (res * sign);
}
