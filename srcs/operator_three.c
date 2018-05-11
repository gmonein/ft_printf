#include "ft_printf.h"

void	do_s(const char **format, va_list ap, t_res *res, t_modifier *mod)
{
	(void)format;
	if (mod->ll || mod->l)
	{
		do_bigs(format, ap, res, mod);
		return ;
	}
	res->res = va_arg(ap, char *);
	res->type = FT_STRING;
	mod->sign = 0;
	mod->space = 0;
	if (res->res == NULL)
		res->res = NULL_STRING;
	res->res_len = strlen(res->res);
}

void	do_percent(const char **format, va_list ap, t_res *res, t_modifier *mod)
{
	(void)ap;
	(void)format;
	res->res = char_alloc('%');
	mod->space = 0;
	res->type = FT_CHAR;
	res->res_len = strlen(res->res);
}
