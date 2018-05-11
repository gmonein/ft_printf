#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <errno.h>
# include <stdio.h>
# include <wchar.h>
# include <locale.h>
# include <limits.h>

# define O_HASH_RES		"0"
# define X_HASH_RES		"0x"
# define XX_HASH_RES		"0X"
# define EMPTY_STRING	""
# define NULL_STRING		"(null)"

# define STR_ULONG_MAX_8 "1777777777777777777777"
# define STR_ZERO	"0"
# define STR_ULLONG_MAX "18446744073709551615"
# define STR_LLONG_MIN "9223372036854775808"

# define BUF_LEN		4096

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

typedef struct		s_res
{
	int				res_len;
	char			*res;
	size_t			var;
	t_type			type;
	int				space_len;
	int				zero_pad;
}					t_res;

typedef struct		s_buf
{
	char			*str;
	size_t			len;
	size_t			i;
}					t_buf;

int		treat(const char **format, va_list ap, t_buf *buf);

wchar_t	*lchar_alloc(wchar_t c);
char	*char_alloc(char c);
char	*string_alloc(char *str);

char	*ltoa_buf(long long nbr, char *signe);
char	*ultoa_buf(unsigned long nbr);
char	*ft_ltoa_hex(unsigned long long nbr, int size, int cap, int base);

int		buf_push_str(t_buf *buf, char *str);
int		buf_push_char(t_buf *buf, char c);
int		buf_push_strn(t_buf *buf, char *str, size_t n);
int		ft_putwchar_buf(t_buf *buf, wchar_t chr);
int		spread_char(t_buf *buf, char c, int cnt);

int		ft_wstrlen(wchar_t *str);
void	ft_putwstrn_buf(t_buf *buf, wchar_t *chr, size_t n);
void	ft_putwstr_buf(t_buf *buf, wchar_t *chr);
int		ft_putwchar_buf(t_buf *buf, wchar_t chr);

void	get_precision(const char **format, t_modifier *mod);
void	get_padding(const char **format, t_modifier *mod);
void	do_modifier_unsigned(size_t *var, t_modifier mod);
void	do_modifier_signed(size_t *var, t_modifier mod);

t_modifier	get_convertion(const char **format);

int		is_digit(char c);


void	do_d(const char **format, va_list ap, t_res *res, t_modifier *mod);
void	do_bigd(const char **format, va_list ap, t_res *res, t_modifier *mod);
void	do_bigu(const char **format, va_list ap, t_res *res, t_modifier *mod);
void	do_u(const char **format, va_list ap, t_res *res, t_modifier *mod);
void	do_o(const char **format, va_list ap, t_res *res, t_modifier *mod);
void	do_bigo(const char **format, va_list ap, t_res *res, t_modifier *mod);
void	do_x(const char **format, va_list ap, t_res *res, t_modifier *mod);
void	do_c(const char **format, va_list ap, t_res *res, t_modifier *mod);
void	do_p(const char **format, va_list ap, t_res *res, t_modifier *mod);
void	do_bigs(const char **format, va_list ap, t_res *res, t_modifier *mod);
void	do_s(const char **format, va_list ap, t_res *res, t_modifier *mod);
void	do_s(const char **format, va_list ap, t_res *res, t_modifier *mod);
void	do_percent(const char **format, va_list ap, t_res *res, t_modifier *mod);

int		ft_printf(const char *format, ...);
char	*ft_sprintf(const char *format, ...);
#endif
