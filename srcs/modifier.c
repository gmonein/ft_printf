#include "ft_printf.h"

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
