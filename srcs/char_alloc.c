# include "ft_printf.h"

char	*string_alloc(char *str)
{
	static char		res[42];

	strcpy(res, str);
	return (res);
}

char	*char_alloc(char c)
{
	static char		res[2] = "\0\0";
	
	res[0] = c;
	return (res);
}

wchar_t	*lchar_alloc(wchar_t c)
{
	static wchar_t		res;

	res = c;
	return (&res);
}
