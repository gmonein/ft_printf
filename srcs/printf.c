# include "ft_printf.h"
# include <limits.h>

typedef struct		s_buf
{
	char			*str;
	size_t			len;
	size_t			i;
}					t_buf;

char	*string_alloc(char *str)
{
	static char		res[42];

	strcpy(res, str);
	return (res);
}

#define STR_ZERO	"0"
#define STR_ULLONG_MAX "18446744073709551615"
#define STR_LLONG_MIN "9223372036854775808"

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

typedef struct		s_modifier
{
	char			l;
	char			ll;
	char			h;
	char			hh;
	char			j;
	char			z;
	char			x;
	char			xx;
	char			hash;
	char			padding;
	char			zero_pad;
	char			precision;
	char			dot;
	char			more;
	char			less;
	char			space;
	char			sign;
	char			*hash_res;
}					t_modifier;

char	*ltoa_buf(long long nbr, char *signe)
{
	static char		res[42];
	int				i;
	int				sign;

	i = 40;
	res[41] = '\0';
	sign = 0;
	if (nbr < 0 && (nbr *= -1))
		sign = 1;
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
	*signe = sign ? '-' : '+';
	return (&res[i + 1]);
}

void	buf_empty(t_buf *buf)
{
	write(1, buf->str, buf->i);
	buf->i = 0;
}

int		buf_push_str(t_buf *buf, char *str)
{
	char		*tmp;
	size_t		len;

	len = strlen(str);
	while (len + buf->i >= buf->len)
	{
		tmp = buf->str;
		buf->str = (char *)malloc(sizeof(char) * buf->len * 2);
		strncpy(buf->str, tmp, buf->len);
		buf->len *= 2;
		free(tmp);
	}
	strcpy(&buf->str[buf->i], str);
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
		strncpy(buf->str, tmp, buf->len);
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
		strncpy(buf->str, tmp, buf->len);
		buf->len *= 2;
		free(tmp);
	}
	strncpy(&buf->str[buf->i], str, n);
	buf->i += n;
	return (0);

}

int			is_convertion(char c)
{
	return (c == 'h' || c == 'l' || c == 'j' || c == 'z' || c == '#'
			|| c == '+' || c == '-' || c == ' ');
}

int		is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

void	get_padding(const char **format, t_modifier *mod)
{
	int			i;

	i = 0;
	if ((*format)[i] == '0')
		mod->zero_pad = 1;
	while (is_digit((*format)[i]))
		i++;
	mod->padding = atoi(*format);
	*format = &(*format)[i];
}

void		get_precision(const char **format, t_modifier *mod)
{
	*format += 1;
	mod->precision = atoi(*format);
	mod->dot = 1;
	while (is_digit(**format))
		*format += 1;
}

t_modifier	get_convertion(const char **format)
{
	t_modifier	res;

	bzero(&res, sizeof(res));
	while (1)
	{
		if (**format == 'h' && (*format += 1))
		{
			if (**format == 'h' && (*format += 1))
				res.hh = 1;
			else
				res.h = 1;
		}
		else if (**format == 'l' && (*format += 1))
		{
			if (**format == 'l' && (*format += 1))
				res.ll = 1;
			else
				res.l = 1;
		}
		else if (**format == 'j' && (*format += 1))
			res.j = 1;
		else if (**format == 'z' && (*format += 1))
			res.z = 1;
		else if (**format == '#' && (*format += 1))
			res.hash = 1;
		else if (**format >= '0' && **format <= '9')
			get_padding(format, &res);
		else if (**format == ' ' && (*format += 1))
			res.space = 1;
		else if (**format == '+' && (*format += 1))
			res.more = 1;
		else if (**format == '-' && (*format += 1))
			res.less = 1;
		else if (**format == '.')
			get_precision(format, &res);
		else
			break ;
	}
	return (res);
}

void	do_modifier_signed(size_t *var, t_modifier mod)
{
	if (mod.ll)
		*var = *((long long *)var);
	else if (mod.l)
		*var = *((long *)var);
	else if (mod.hh)
		*var = *((char *)var);
	else if (mod.h)
		*var = *((short *)var);
	else if (mod.j)
		*var = *((intmax_t *)var);
	else if (mod.z)
		*var = *((long long *)var);
	else
		*var = *((int *)var);
}

void	do_modifier_unsigned(size_t *var, t_modifier mod)
{
	if (mod.ll)
		*var = *((unsigned long long *)var);
	else if (mod.l)
		*var = *((unsigned long *)var);
	else if (mod.hh)
		*var = *((unsigned char *)var);
	else if (mod.h)
		*var = *((unsigned short *)var);
	else if (mod.j)
		*var = *((intmax_t *)var);
	else if (mod.z)
		*var = *((unsigned long long *)var);
	else
		*var = *((unsigned int *)var);
}

#define STR_ULONG_MAX_8 "1777777777777777777777"

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

void	print_padding(t_modifier *mod, int act_len,
					t_buf *buf)
{
	mod->padding -= act_len;
	if (mod->padding < 0)
		return ;
	while (mod->padding != 0)
	{
		if (mod->less)
			mod->zero_pad = 0;
		buf_push_char(buf, mod->zero_pad ? '0' : ' ');
		mod->padding--;
	}
}

#define O_HASH_RES		"0"
#define X_HASH_RES		"0x"
#define XX_HASH_RES		"0X"
#define EMPTY_STRING	""
#define NULL_STRING		"(null)"

typedef enum		e_type
{
	FT_NUMBER,
	FT_NONE,
	FT_WCHAR,
	FT_SWCHAR,
	FT_HEX,
	FT_CHAR,
	FT_STRING
}					t_type;

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

int		treat(const char **format, va_list ap, t_buf *buf)
{
	char			*res;
	t_modifier		mod;
	size_t			var;
	t_type			type;
	int				res_len;

	*format += 1;
	mod = get_convertion(format);
	if (**format == 'd' || **format == 'D' || **format == 'i' || **format == 'I')
	{
		if (**format == 'D' || **format == 'I')
			mod.ll = 1;
		var = va_arg(ap, size_t);
		do_modifier_signed(&var, mod);
		res = ltoa_buf(var, &mod.sign);
		type = FT_NUMBER;
		if (var == 0 && mod.dot && !mod.precision)
			res = EMPTY_STRING;
		res_len = strlen(res);
	}
	else if (**format == 'u' || **format == 'U')
	{
		if (**format == 'U')
			mod.ll = 1;
		mod.more = 0;
		mod.space = 0;
		var = va_arg(ap, size_t);
		do_modifier_unsigned(&var, mod);
		res = ultoa_buf(var);
		type = FT_NUMBER;
		if (var == 0 && mod.dot && !mod.precision)
			res = EMPTY_STRING;
		res_len = strlen(res);
	}
	else if (**format == 'o' || **format == 'O')
	{
		var = va_arg(ap, size_t);
		if (**format == 'O')
			mod.ll = 1;
		do_modifier_unsigned(&var, mod);
		res = ft_ltoa_hex(var, 999, **format == 'o' ? 0 : 1, 8);
		mod.space = 0;
		mod.more = 0;
		if (mod.hash)
		{
			mod.hash_res = O_HASH_RES;
			mod.padding -= 1;
		}
		type = FT_NUMBER;
		if (var == 0 && ((mod.dot && !mod.precision) || mod.hash))
			res = EMPTY_STRING;
		res_len = strlen(res);
	}
	else if (**format == 'x' || **format == 'X')
	{
		var = va_arg(ap, size_t);
		do_modifier_unsigned(&var, mod);
		res = ft_ltoa_hex(var, 16, **format == 'x' ? 0 : 1, 16);
		mod.more = 0;
		if (mod.hash && var != 0)
		{
			mod.hash_res = **format == 'x' ? X_HASH_RES : XX_HASH_RES;
			mod.padding -= 2;
		}
		type = FT_HEX;
		if (var == 0 && mod.dot && !mod.precision)
			res = EMPTY_STRING;
		res_len = strlen(res);
		mod.space = 0;
	}
	else if (**format == 'c' || **format == 'C')
	{
		var = va_arg(ap, size_t);
		if (**format == 'C' || mod.l || mod.ll)
		{
			type = FT_WCHAR;
			res = lchar_alloc(var);
			res_len = 1;
		}
		else
		{
			type = FT_CHAR;
			res = char_alloc(var);
			res_len = 1;
		}
		mod.space = 0;
	}
	else if (**format == 'p')
	{
		var = va_arg(ap, size_t);
		res = ft_ltoa_hex(var, -1, 0, 16);
		mod.hash_res = X_HASH_RES;
		mod.padding -= 2;
		mod.space = 0;
		type = FT_HEX;
		res_len = strlen(res);
		if (mod.dot && mod.precision == 0 && var == 0)
			res_len = 0;
	}
	else if (**format == 'S' || (**format == 's' && (mod.l || mod.ll)))
	{
		res = va_arg(ap, char *);
		type = FT_SWCHAR;
		mod.sign = 0;
		mod.space = 0;
		if (res == NULL)
		{
			res = NULL_STRING;
			res_len = strlen(res);
			type = FT_STRING;
		}
		else
			res_len = ft_wstrlen((wchar_t *)res);
	}
	else if (**format == 's')
	{
		res = va_arg(ap, char *);
		type = FT_STRING;
		mod.sign = 0;
		mod.space = 0;
		if (res == NULL)
			res = NULL_STRING;
		res_len = strlen(res);
	}
	else if (**format == '%')
	{
		res = char_alloc('%');
		mod.space = 0;
		type = FT_CHAR;
		res_len = strlen(res);
	}
	else
	{
		if (!**format)
			return (1);
		res = char_alloc(**format);
		mod.space = 0;
		res_len = 1;
		type = FT_NONE;
	}
	if (mod.less)
		mod.zero_pad = 0;
	if (mod.sign == '+' && !mod.more)
		mod.sign = '\0';
	if (mod.sign && mod.space)
		mod.space = '\0';
	if (mod.sign || mod.space)
		mod.padding -= 1;

	int		space_len;
	int		zero_pad;

	zero_pad = 0;
	if (mod.dot)
	{
		if ((type == FT_STRING || type == FT_SWCHAR) && mod.precision < res_len)
			res_len = mod.precision;
		else if (type == FT_HEX || type == FT_NUMBER)
			zero_pad = mod.precision - res_len;
		else if (mod.zero_pad && !mod.less)
			zero_pad = mod.padding - res_len;
	}
	else if (mod.zero_pad > 0)
			zero_pad = mod.padding - res_len;
	space_len = mod.padding - res_len;
	if (zero_pad > 0)
		space_len -= zero_pad;
	if (mod.precision > mod.padding)
		mod.padding = mod.precision;
	if (!mod.less)
		space_len = spread_char(buf, ' ', space_len);
	if (mod.space)
		buf_push_char(buf, ' ');
	if (mod.sign)
		buf_push_char(buf, mod.sign);
	if (mod.hash_res)
		buf_push_str(buf, mod.hash_res);
	spread_char(buf, '0', zero_pad);
	if (type == FT_WCHAR)
		ft_putwstrn_buf(buf, (wchar_t *)res, 1);
	else if (type == FT_SWCHAR && mod.dot)
		ft_putwstrn_buf(buf, (wchar_t *)res, res_len);
	else if (type == FT_SWCHAR)
		ft_putwstr_buf(buf, (wchar_t *)res);
	else
		buf_push_strn(buf, res, res_len);
	spread_char(buf, ' ', space_len);
	*format += 1;
	return (1);
}

#define BUF_LEN		1024

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
