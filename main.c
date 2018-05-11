#include <stdio.h>

#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <locale.h>
#include <stdio.h>
#include <wchar.h>
int	ft_printf(const char *format, ...);

int	main(int argc, char **argv)
{
	int a = 0;
	if (a)
	{
	printf("format: %s\n", argv[1]);
	printf(argv[1], argv[2]);
	printf("\n");
	ft_printf(argv[1], argv[2]);
	printf("\n");
	}

	setlocale(LC_ALL, "");
	/*
	printf("%S", L"Á±≥");
	printf("\n");
	ft_printf("%S", L"Á±≥");
	printf("\n");
	printf("%S", NULL);
	printf("\n");
	ft_printf("%S", NULL);
	printf("\n");
	*/
	printf("%.4S\n", L"ÊM-M-^QÊM-^XØ‰∏M-ÂM-^O™ÁM-^L´„M-M-^B");
	ft_printf("%.4S\n", L"ÊM-M-^QÊM-^XØ‰∏M-ÂM-^O™ÁM-^L´„M-M-^B");
	printf("{%05.c}\n", 0);
	ft_printf("{%05.c}\n", 0);
	printf("%o\n", ULONG_MAX);
	printf("%O\n", ULONG_MAX);
	ft_printf("%o\n", ULONG_MAX);
	ft_printf("%O\n", ULONG_MAX);
	printf("%o\n", LONG_MAX);
	printf("%O\n", LONG_MAX);
	ft_printf("%o\n", LONG_MAX);
	ft_printf("%O\n", LONG_MAX);
	printf("% x|%+x\n", 42, 42);
	ft_printf("% x|%+x\n", 42, 42);
	printf("%8.4o\n", 42424242424);
	ft_printf("%8.4o\n", 42424242424);
	printf("%.p, %.0p\n", 0, 0);
	ft_printf("%.p, %.0p\n", 0, 0);
	printf("{%05s}\n", "abc");
	ft_printf("{%05s}\n", "abc");
	printf("{%30S}\n", L"ÊM-M-^QÊM-^XØ‰∏M-ÂM-^O™ÁM-^L´„M-M-^B");
	ft_printf("{%30S}\n", L"ÊM-M-^QÊM-^XØ‰∏M-ÂM-^O™ÁM-^L´„M-M-^B");
	printf("{%030S}\n", L"ÊM-M-^QÊM-^XØ‰∏M-ÂM-^O™ÁM-^L´„M-M-^B");
	ft_printf("{%030S}\n", L"ÊM-M-^QÊM-^XØ‰∏M-ÂM-^O™ÁM-^L´„M-M-^B");
	printf("{%03c}\n", 0);
	ft_printf("{%03c}\n", 0);
	printf("%hhC, %hhC\n", 0, L'Á±≥');
	ft_printf("%hhC, %hhC\n", 0, L'Á±≥');
	printf("%lc, %lc", L'ÊM-^ZM-^V', L'ÿ≠');
	printf("\n");
	ft_printf("%lc, %lc", L'ÊM-^ZM-^V', L'ÿ≠');
	printf("\n");
	printf("%.35S", L"ÊM-M-^QÊM-^XØ‰∏M-ÂM-^O™ÁM-^L´„M-M-^B");
	printf("\n");
	ft_printf("%.35S", L"ÊM-M-^QÊM-^XØ‰∏M-ÂM-^O™ÁM-^L´„M-M-^B");
	printf("\n");
}
