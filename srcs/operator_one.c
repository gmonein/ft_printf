# include "ft_printf.h"

void	do_d(const char **format, va_list ap, t_res *res, t_modifier *mod)
{
	(void)format;
	res->var = va_arg(ap, size_t);
	do_modifier_signed(&res->var, *mod);
	res->res = ltoa_buf(res->var, &mod->sign);
	res->type = FT_NUMBER;
	if (res->var == 0 && mod->dot && !mod->precision)
		res->res = EMPTY_STRING;
	res->res_len = strlen(res->res);
}

void	do_bigd(const char **format, va_list ap, t_res *res, t_modifier *mod)
{
	(void)format;
	mod->ll = 1;
	res->var = va_arg(ap, size_t);
	do_modifier_signed(&res->var, *mod);
	res->res = ltoa_buf(res->var, &mod->sign);
	res->type = FT_NUMBER;
	if (res->var == 0 && mod->dot && !mod->precision)
		res->res = EMPTY_STRING;
	res->res_len = strlen(res->res);
}

void	do_bigu(const char **format, va_list ap, t_res *res, t_modifier *mod)
{
	(void)format;
	mod->ll = 1;
	res->var = va_arg(ap, size_t);
	mod->space = 0;
	mod->more = 0;
	do_modifier_unsigned(&res->var, *mod);
	res->res = ultoa_buf(res->var);
	res->type = FT_NUMBER;
	if (res->var == 0 && mod->dot && !mod->precision)
		res->res = EMPTY_STRING;
	res->res_len = strlen(res->res);
}

void	do_u(const char **format, va_list ap, t_res *res, t_modifier *mod)
{
	(void)format;
	res->var = va_arg(ap, size_t);
	mod->space = 0;
	mod->more = 0;
	do_modifier_unsigned(&res->var, *mod);
	res->res = ultoa_buf(res->var);
	res->type = FT_NUMBER;
	if (res->var == 0 && mod->dot && !mod->precision)
		res->res = EMPTY_STRING;
	res->res_len = strlen(res->res);
}

void	do_o(const char **format, va_list ap, t_res *res, t_modifier *mod)
{
	(void)format;
	res->var = va_arg(ap, size_t);
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
