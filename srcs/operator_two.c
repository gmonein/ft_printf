# include "ft_printf.h"

void	do_bigo(const char **format, va_list ap, t_res *res, t_modifier *mod)
{
	(void)format;
	res->var = va_arg(ap, size_t);
	mod->ll = 1;
	do_modifier_unsigned(&res->var, *mod);
	res->res = ft_ltoa_hex(res->var, 999, **format == 'o' ? 0 : 1, 8);
	mod->space = 0;
	mod->more = 0;
	if (mod->hash)
	{
		mod->hash_res = O_HASH_RES;
		mod->padding -= 1;
	}
	res->type = FT_NUMBER;
	if (res->var == 0 && ((mod->dot && !mod->precision) || mod->hash))
		res->res = EMPTY_STRING;
	res->res_len = strlen(res->res);
}

void	do_x(const char **format, va_list ap, t_res *res, t_modifier *mod)
{
	(void)format;
	res->var = va_arg(ap, size_t);
	do_modifier_unsigned(&res->var, *mod);
	res->res = ft_ltoa_hex(res->var, 16, **format == 'x' ? 0 : 1, 16);
	mod->more = 0;
	if (mod->hash && res->var != 0)
	{
		mod->hash_res = **format == 'x' ? X_HASH_RES : XX_HASH_RES;
		mod->padding -= 2;
	}
	res->type = FT_HEX;
	if (res->var == 0 && mod->dot && !mod->precision)
		res->res = EMPTY_STRING;
	res->res_len = strlen(res->res);
	mod->space = 0;
}

void	do_c(const char **format, va_list ap, t_res *res, t_modifier *mod)
{
	res->var = va_arg(ap, size_t);
	if (**format == 'C' || mod->l || mod->ll)
	{
		res->type = FT_WCHAR;
		res->res = (char *)lchar_alloc(res->var);
	}
	else
	{
		res->type = FT_CHAR;
		res->res = char_alloc(res->var);
	}
	res->res_len = 1;
	mod->space = 0;
}

void	do_p(const char **format, va_list ap, t_res *res, t_modifier *mod)
{
	(void)format;
	res->var = va_arg(ap, size_t);
	res->res = ft_ltoa_hex(res->var, -1, 0, 16);
	mod->hash_res = X_HASH_RES;
	mod->padding -= 2;
	mod->space = 0;
	res->type = FT_HEX;
	res->res_len = strlen(res->res);
	if (mod->dot && mod->precision == 0 && res->var == 0)
		res->res_len = 0;
}

void	do_bigs(const char **format, va_list ap, t_res *res, t_modifier *mod)
{
	(void)format;
	res->res = va_arg(ap, char *);
	res->type = FT_SWCHAR;
	mod->sign = 0;
	mod->space = 0;
	if (res->res == NULL)
	{
		res->res = NULL_STRING;
		res->res_len = strlen(res->res);
		res->type = FT_STRING;
	}
	else
		res->res_len = ft_wstrlen((wchar_t *)res->res);
}
