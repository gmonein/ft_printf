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

void (*g_fct[CHAR_MAX])(const char **, va_list, t_res *, t_modifier *) =
{
	['d'] = do_d,
	['D'] = do_bigd,
	['I'] = do_bigd,
	['i'] = do_d,
	['u'] = do_u,
	['U'] = do_bigu,
	['o'] = do_o,
	['O'] = do_bigo,
	['x'] = do_x,
	['X'] = do_x,
	['c'] = do_c,
	['C'] = do_c,
	['s'] = do_s,
	['S'] = do_bigs,
	['p'] = do_p,
	['%'] = do_percent
};

void	solve_modifier(t_modifier *mod)
{
	if (mod->less)
		mod->zero_pad = 0;
	if (mod->sign == '+' && !mod->more)
		mod->sign = '\0';
	if (mod->sign && mod->space)
		mod->space = '\0';
	if (mod->sign || mod->space)
		mod->padding -= 1;
}

void	print_bis(const char **format, t_buf *buf, t_modifier *mod, t_res *res)
{
	if (res->zero_pad > 0)
		res->space_len -= res->zero_pad;
	if (mod->precision > mod->padding)
		mod->padding = mod->precision;
	if (!mod->less)
		res->space_len = spread_char(buf, ' ', res->space_len);
	if (mod->space)
		buf_push_char(buf, ' ');
	if (mod->sign)
		buf_push_char(buf, mod->sign);
	if (mod->hash_res)
		buf_push_str(buf, mod->hash_res);
	spread_char(buf, '0', res->zero_pad);
	if (res->type == FT_WCHAR)
		ft_putwstrn_buf(buf, (wchar_t *)res->res, 1);
	else if (res->type == FT_SWCHAR && mod->dot)
		ft_putwstrn_buf(buf, (wchar_t *)res->res, res->res_len);
	else if (res->type == FT_SWCHAR)
		ft_putwstr_buf(buf, (wchar_t *)res->res);
	else
		buf_push_strn(buf, res->res, res->res_len);
	spread_char(buf, ' ', res->space_len);
	*format += 1;
}

void	print(const char **format, t_buf *buf, t_modifier *mod, t_res *res)
{
	res->zero_pad = 0;
	if (mod->dot)
	{
		if ((res->type == FT_STRING || res->type == FT_SWCHAR)
			&& mod->precision < res->res_len)
			res->res_len = mod->precision;
		else if (res->type == FT_HEX || res->type == FT_NUMBER)
			res->zero_pad = mod->precision - res->res_len;
		else if (mod->zero_pad && !mod->less)
			res->zero_pad = mod->padding - res->res_len;
	}
	else if (mod->zero_pad > 0)
		res->zero_pad = mod->padding - res->res_len;
	res->space_len = mod->padding - res->res_len;
	print_bis(format, buf, mod, res);
}

int		treat(const char **format, va_list ap, t_buf *buf)
{
	t_modifier		mod;
	t_res			m_res;

	*format += 1;
	get_convertion(format, &mod);
	if (g_fct[(int)**format])
		g_fct[(int)**format](format, ap, &m_res, &mod);
	else
	{
		if (!**format)
			return (1);
		m_res.res = char_alloc(**format);
		mod.space = 0;
		m_res.res_len = 1;
		m_res.type = FT_NONE;
	}
	solve_modifier(&mod);
	print(format, buf, &mod, &m_res);
	return (1);
}
