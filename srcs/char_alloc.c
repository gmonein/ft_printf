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

char	*string_alloc(char *str)
{
	static char		res[42];

	ft_strcpy(res, str);
	return (res);
}

char	*char_alloc(char c)
{
	static char		res[2] = "\0\0";

	res[0] = c;
	return (res);
}

wchar_t	*lchar_alloc(wchar_t c)
{
	static wchar_t		res;

	res = c;
	return (&res);
}
