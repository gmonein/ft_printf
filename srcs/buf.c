/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <gmonein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 20:42:49 by gmonein           #+#    #+#             */
/*   Updated: 2018/03/06 14:31:23 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		spread_char(t_buf *buf, char c, int cnt)
{
	char	str[4];

	if (cnt > 4)
	{
		str[0] = c;
		str[1] = c;
		str[2] = c;
		str[3] = c;
		while (cnt - 4 > 0)
		{
			buf_push_strn(buf, str, 4);
			cnt -= 4;
		}
	}
	while (cnt > 0)
	{
		buf_push_char(buf, c);
		cnt--;
	}
	return (cnt);
}

int		buf_push_str(t_buf *buf, char *str)
{
	char		*tmp;
	size_t		len;

	len = ft_strlen(str);
	while (len + buf->i >= buf->len)
	{
		tmp = buf->str;
		buf->str = (char *)malloc(sizeof(char) * buf->len * 2);
		ft_strncpy(buf->str, tmp, buf->len);
		buf->len *= 2;
		free(tmp);
	}
	ft_strcpy(&buf->str[buf->i], str);
	buf->i += len;
	return (0);
}

int		buf_push_char(t_buf *buf, char c)
{
	char		*tmp;

	if (buf->i + 1 >= buf->len)
	{
		tmp = buf->str;
		buf->str = (char *)malloc(sizeof(char) * buf->len * 2);
		ft_strncpy(buf->str, tmp, buf->len);
		buf->len *= 2;
		free(tmp);
	}
	buf->str[buf->i] = c;
	buf->i++;
	return (0);
}

int		buf_push_strn(t_buf *buf, char *str, size_t n)
{
	char		*tmp;

	while (n + buf->i > buf->len - 4)
	{
		tmp = buf->str;
		buf->str = (char *)malloc(sizeof(char) * buf->len * 2);
		ft_strncpy(buf->str, tmp, buf->len);
		buf->len *= 2;
		free(tmp);
	}
	ft_strncpy(&buf->str[buf->i], str, n);
	buf->i += n;
	return (0);
}
