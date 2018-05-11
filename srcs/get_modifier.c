# include "ft_printf.h"

int		get_convertion_bis(const char **format, t_modifier *mod)
{
	if (**format == 'z' && (*format += 1))
		mod->z = 1;
	else if (**format == '#' && (*format += 1))
		mod->hash = 1;
	else if (**format >= '0' && **format <= '9')
		get_padding(format, mod);
	else if (**format == ' ' && (*format += 1))
		mod->space = 1;
	else if (**format == '+' && (*format += 1))
		mod->more = 1;
	else if (**format == '-' && (*format += 1))
		mod->less = 1;
	else if (**format == '.')
		get_precision(format, mod);
	else
		return (0);
	return (1);
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
		else if (!get_convertion_bis(format, &res))
			break ;
	}
	return (res);
}
