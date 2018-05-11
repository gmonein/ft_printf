/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wchar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <gmonein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 20:42:49 by gmonein           #+#    #+#             */
/*   Updated: 2018/03/06 14:31:23 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_putwchar_buf(t_buf *buf, wchar_t chr)
{
	int		ret;

	ret = 0;
	if (chr <= 0x7F && (ret = 1))
		buf_push_char(buf, chr);
	else if (chr <= 0x7FF && (ret = 2))
	{
		buf_push_char(buf, (chr >> 6) | 0xC0);
		buf_push_char(buf, (chr & 0x3F) | 0x80);
	}
	else if (chr <= 0xFFFF && (ret = 3))
	{
		buf_push_char(buf, (chr >> 12) | 0xE0);
		buf_push_char(buf, ((chr >> 6) & 0x3F) | 0x80);
		buf_push_char(buf, (chr & 0x3F) | 0x80);
	}
	else if (chr <= 0x10FFFF && (ret = 4))
	{
		buf_push_char(buf, (chr >> 18) | 0xF0);
		buf_push_char(buf, ((chr >> 12) & 0x3F) | 0x80);
		buf_push_char(buf, ((chr >> 6) & 0x3F) | 0x80);
		buf_push_char(buf, (chr & 0x3F) | 0x80);
	}
	return (ret);
}

void	ft_putwstr_buf(t_buf *buf, wchar_t *chr)
{
	int		i;

	i = 0;
	while (chr[i])
	{
		ft_putwchar_buf(buf, chr[i]);
		i++;
	}
}

void	ft_putwstrn_buf(t_buf *buf, wchar_t *chr, size_t n)
{
	size_t	i;
	int		j;

	i = 0;
	j = n;
	while (i < n && j > 0)
	{
		j -= ft_putwchar_buf(buf, chr[i]);
		i++;
	}
}

int		ft_wstrlen(wchar_t *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
