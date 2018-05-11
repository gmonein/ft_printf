/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <gmonein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 20:42:49 by gmonein           #+#    #+#             */
/*   Updated: 2018/03/06 14:31:23 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_STRUCT_H
# define FT_PRINTF_STRUCT_H

# include <stdlib.h>
# define O_HASH_RES "0"
# define X_HASH_RES "0x"
# define XX_HASH_RES "0X"
# define EMPTY_STRING ""
# define NULL_STRING "(null)"

# define STR_ULONG_MAX_8 "1777777777777777777777"
# define STR_ZERO "0"
# define STR_ULLONG_MAX "18446744073709551615"
# define STR_LLONG_MIN "9223372036854775808"

# define BUF_LEN 4096

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

#endif
