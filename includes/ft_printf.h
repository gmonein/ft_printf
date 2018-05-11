/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <gmonein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 20:42:49 by gmonein           #+#    #+#             */
/*   Updated: 2018/03/06 14:31:23 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <errno.h>
# include <stdio.h>
# include <wchar.h>
# include <locale.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include "ft_printf_struct.h"

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

void	get_convertion(const char **format, t_modifier *mod);

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
void	do_percent(const char **forma, va_list ap, t_res *res, t_modifier *mod);

int		ft_printf(const char *format, ...);
char	*ft_sprintf(const char *format, ...);
void	*ft_bzero(void *ptr, size_t num);
char	*ft_strncpy(char *dst, char *src, size_t n);
char	*ft_strcpy(char *dest, const char *src);
size_t	ft_strlen(const char *str);
int		ft_atoi(const char *str);

#endif
