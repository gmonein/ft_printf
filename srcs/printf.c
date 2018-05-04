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
#define STR_ULLONG_MAX "9223372036854775807"
#define STR_LLONG_MIN "9223372036854775808"

char	*char_alloc(char c)
{
	static char		res[2] = "\0\0";
	
	res[0] = c;
	return (res);
}

char	*ultoa_buf(unsigned long nbr)
{
	static char		res[42];
	int				i;

	i = 40;
	res[41] = '\0';
	if (nbr == 0)
		return (STR_ZERO);
	if (nbr == ULLONG_MAX)
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
	buf->str[buf->i] = '\0';
	return (0);
}

int		buf_push_strn(t_buf *buf, char *str, size_t n)
{
	char		*tmp;
	size_t		len;

	len = strlen(str);
	if (n < len)
		len = n;
	while (len + buf->i >= buf->len)
	{
		tmp = buf->str;
		buf->str = (char *)malloc(sizeof(char) * buf->len * 2);
		strncpy(buf->str, tmp, buf->len);
		buf->len *= 2;
		free(tmp);
	}
	strncpy(&buf->str[buf->i], str, n);
	buf->i += len;
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
		*var = *((size_t *)var);
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
		*var = *((size_t *)var);
	else
		*var = *((unsigned int *)var);
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
	FT_HEX,
	FT_CHAR,
	FT_STRING
}					t_type;

int		treat(const char **format, va_list ap, t_buf *buf)
{
	char			*res;
	t_modifier		mod;
	size_t			var;
	t_type			type;

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
	}
	else if (**format == 'o' || **format == 'O')
	{
		var = va_arg(ap, size_t);
		do_modifier_unsigned(&var, mod);
		res = ft_ltoa_hex(var, mod.padding, **format == 'o' ? 0 : 1, 8);
		mod.space = 0;
		mod.more = 0;
		mod.less = 0;
		if (mod.hash)
		{
			mod.hash_res = O_HASH_RES;
			mod.padding -= 1;
		}
		type = FT_NUMBER;
		if (var == 0 && ((mod.dot && !mod.precision) || mod.hash))
			res = EMPTY_STRING;
	}
	else if (**format == 'x' || **format == 'X')
	{
		var = va_arg(ap, size_t);
		res = ft_ltoa_hex(var, mod.j || mod.ll || mod.l ?
				16 : 8, **format == 'x' ? 0 : 1, 16);
		mod.more = 0;
		if (mod.hash && var != 0)
		{
			mod.hash_res = **format == 'x' ? X_HASH_RES : XX_HASH_RES;
			mod.padding -= 2;
		}
		type = FT_HEX;
		if (var == 0 && mod.dot && !mod.precision)
			res = EMPTY_STRING;
	}
	else if (**format == 'c' || **format == 'C')
	{
		var = va_arg(ap, size_t);
		res = char_alloc(var);
		mod.space = 0;
		if (var == 0)
			buf_push_char(buf, '\0');
		type = FT_CHAR;
	}
	else if (**format == 'p')
	{
		var = va_arg(ap, size_t);
		res = ft_ltoa_hex(var, -1, 0, 16);
		mod.hash_res = X_HASH_RES;
		mod.padding -= 2;
		mod.space = 0;
		type = FT_HEX;
	}
	else if (**format == 's')
	{
		res = va_arg(ap, char *);
		type = FT_STRING;
		if (res == NULL)
			res = NULL_STRING;
	}
	else if (**format == '%')
	{
		res = char_alloc('%');
		mod.space = 0;
		type = FT_CHAR;
	}
	else
		return (0);
	if (mod.less)
		mod.zero_pad = 0;
	if (mod.sign == '+' && !mod.more)
		mod.sign = '\0';
	if (mod.sign && mod.space)
		mod.space = '\0';

	int		res_len;
	int		space_len;
	int		zero_pad;

	res_len = strlen(res);
	if (res_len == 0 && type == FT_CHAR)
		res_len = 1;
	zero_pad = 0;
	if (mod.sign)
		mod.padding -= 1;
	if (mod.dot)
	{
		if (type == FT_STRING && mod.precision < res_len)
			res_len = mod.precision;
		else if (type == FT_HEX || type == FT_NUMBER)
			zero_pad = mod.precision - res_len;
	}
	else if (type == FT_HEX || type == FT_NUMBER)
		if (mod.zero_pad)
			zero_pad = mod.padding - res_len;
	space_len = mod.padding - res_len;
	if (zero_pad > 0)
	{
		mod.space = 0;
		space_len--;
	}
	if (!mod.less)
	{
		while (space_len > 0)
		{
			buf_push_char(buf, ' ');
			space_len--;
		}
	}
	if (mod.space)
		buf_push_char(buf, ' ');
	if (mod.sign)
		buf_push_char(buf, mod.sign);
	if (mod.hash_res)
		buf_push_str(buf, mod.hash_res);
	while (zero_pad > 0)
	{
		buf_push_char(buf, '0');
		zero_pad--;
	}
	buf_push_strn(buf, res, res_len);
	while (space_len > 0)
	{
		buf_push_char(buf, ' ');
		space_len--;
	}
	*format += 1;
	return (1);
}

#define BUF_LEN		1024

void	do_printf(const char *format, va_list ap, t_buf *buf)
{
	int			treated;

	buf->str = (char *)malloc(sizeof(char) * BUF_LEN);
	buf->len = BUF_LEN;
	buf->i = 0;
	while (*format)
	{
		if (*format == '%')
			treated = treat(&format, ap, buf);
		if (treated == 0)
		{
			buf_push_char(buf, *format);
			format++;
		}
		treated = 0;
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
