# include "ft_printf.h"

int			is_convertion(char c)
{
	return (c == 'h' || c == 'l' || c == 'j' || c == 'z' || c == '#'
			|| c == '+' || c == '-' || c == ' ');
}

int		is_digit(char c)
{
	return (c >= '0' && c <= '9');
}
