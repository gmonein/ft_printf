#include "ft_printf.h"

void	do_printf(const char *format, va_list ap, t_buf *buf)
{
	buf->str = (char *)malloc(sizeof(char) * BUF_LEN);
	buf->len = BUF_LEN;
	buf->i = 0;
	while (*format)
	{
		if (*format == '%')
			treat(&format, ap, buf);
		else
		{
			buf_push_char(buf, *format);
			format++;
		}
	}
}

char	*ft_sprintf(const char *format, ...)
{
	va_list		ap;
	t_buf		buf;

	va_start(ap, format);
	do_printf(format, ap, &buf);
	va_end(ap);
	return (buf.str);
}

int		ft_printf(const char *format, ...)
{
	t_buf		buf;
	va_list		ap;

	va_start(ap, format);
	do_printf(format, ap, &buf);
	va_end(ap);
	write(1, buf.str, buf.i);
	free(buf.str);
	return (buf.i);
}
