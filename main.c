#include <stdio.h>

#include <string.h>
#include <unistd.h>
#include <limits.h>
int	ft_printf(const char *format, ...);

int	main(int argc, char **argv)
{
char		format[1000];
	strcpy(format, "% # -O\n");
	printf("\n%s", format);
	ft_printf(format, LLONG_MIN);
	printf(format, LLONG_MIN);

	strcpy(format, " 4.5i\n");
	printf("\n%s", format);
	ft_printf(format, 42);
	printf(format, 42);

	strcpy(format, "% # -O\n");
	printf("\n%s", format);
	ft_printf(format, 42);
	printf(format, 42);

	strcpy(format, "% # -O\n");
	printf("\n%s", format);
	ft_printf(format, 42);
	printf(format, 42);

}
