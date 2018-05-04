#include <stdio.h>

#include <string.h>
#include <unistd.h>
#include <limits.h>
int	ft_printf(const char *format, ...);

int	main(int argc, char **argv)
{
char		format[1000];
	strcpy(format, "%p\n");
	printf("\n%s", format);
	ft_printf(format, format);
	printf(format, format);

	strcpy(format, "%0p\n");
	printf("\n%s", format);
	ft_printf(format, format);
	printf(format, format);

	strcpy(format, "%0p\n");
	printf("\n%s", format);
	ft_printf(format, NULL);
	printf(format, NULL);

	strcpy(format, "% 0p\n");
	printf("\n%s", format);
	ft_printf(format, format);
	printf(format, format);

	strcpy(format, "%o\n");
	printf("\n%s", format);
	ft_printf(format, LLONG_MIN);
	printf(format, LLONG_MIN);

	strcpy(format, "%zi\n");
	printf("\n%s", format);
	ft_printf(format, LLONG_MIN);
	printf(format, LLONG_MIN);

	strcpy(format, "% O\n");
	printf("\n%s", format);
	ft_printf(format, LLONG_MIN);
	printf(format, LLONG_MIN);

	strcpy(format, "% # -O\n");
	printf("\n%s", format);
	ft_printf(format, LLONG_MIN);
	printf(format, LLONG_MIN);

}
