#include "ft_printf.h"

int		ft_putwchar_buf(t_buf *buf, wchar_t chr)
{
	if (chr <= 0x7F)
	{
		buf_push_char(buf, chr);
		return (1);
	}
	else if (chr <= 0x7FF)
	{
		buf_push_char(buf, (chr >> 6) | 0xC0);
		buf_push_char(buf, (chr & 0x3F) | 0x80);
		return (2);
	}
	else if (chr <= 0xFFFF)
	{
		buf_push_char(buf, (chr >> 12) | 0xE0);
		buf_push_char(buf, ((chr >> 6) & 0x3F) | 0x80);
		buf_push_char(buf, (chr & 0x3F) | 0x80);
		return (3);
	}
	else if (chr <= 0x10FFFF)
	{
		buf_push_char(buf, (chr >> 18) | 0xF0);
		buf_push_char(buf, ((chr >> 12) & 0x3F) | 0x80);
		buf_push_char(buf, ((chr >> 6) & 0x3F) | 0x80);
		buf_push_char(buf, (chr & 0x3F) | 0x80);
		return (4);
	}
	return (0);
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
