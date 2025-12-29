#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "libasm_bonus.h"

int	checkerror(char *str)
{
	int	i;
	int	j;

	i = 0;
	if (str[0] == '\0' || str[1] == '\0')
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] <= 32 || str[i] == 127 || str[i] == 43 || str[i] == 45)
			return (0);
		j = i + 1;
		while (str[j] != '\0')
		{
			if (str[i] == str[j])
				return (0);
			j++;
		}
		i++;
	}
	return (i);
}

int	nb_base(char str, char *base)
{
	int	nb;

	nb = 0;
	while (base[nb] != '\0')
	{
		if (str == base[nb])
			return (nb);
		nb++;
	}
	return (-1);
}

int	whitespaces(char *str, int *ptr_i)
{
	int	count;
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	count = 1;
	while (str[i] && (str[i] == 43 || str[i] == 45))
	{
		if (str[i] == 45)
			count *= -1;
		i++;
	}
	*ptr_i = i;
	return (count);
}

int	ft_atoi_base_piscine(char *str, char *base)
{
	int		i;
	int		negative;
	int		nb;
	int		nb2;
	int		begin_len;

	nb = 0;
	i = 0;
	begin_len = checkerror(base);
	if (begin_len >= 2)
	{
		negative = whitespaces(str, &i);
		nb2 = nb_base(str[i], base);
		while (nb2 != -1)
		{
			nb = (nb * begin_len) + nb2;
			i++;
			nb2 = nb_base(str[i], base);
		}
		return (nb *= negative);
	}
	return (0);
}

/* --------------------------------------------------------- 
    Benchmark helper 
--------------------------------------------------------- */ 
static long ns_diff(struct timespec a, struct timespec b)
{
    return (b.tv_sec - a.tv_sec) * 1000000000L + (b.tv_nsec - a.tv_nsec);
}

/* ---------------------------------------------------------
   Test interactivo + benchmark
   --------------------------------------------------------- */
void test_atoi_base(void)
{
    printf("\n=== TEST INTERACTIVO ft_atoi_base + BENCHMARK ===\n");
    printf("Introduce una cadena y una base para convertir.\n");
    printf("Escribe \"exit\" en cualquiera de los campos para salir.\n\n");

    char str[256];
    char base[256];

    while (1)
    {
        printf("Cadena: ");
        fflush(stdout);

        if (!fgets(str, sizeof(str), stdin))
        {
            printf("Error leyendo entrada.\n");
            break;
        }

        str[strcspn(str, "\n")] = '\0';
        if (strcmp(str, "exit") == 0)
            break;

        printf("Base:   ");
        fflush(stdout);

        if (!fgets(base, sizeof(base), stdin))
        {
            printf("Error leyendo entrada.\n");
            break;
        }

        base[strcspn(base, "\n")] = '\0';
        if (strcmp(base, "exit") == 0)
            break;

        /* --- Comparación funcional --- */
        int a = ft_atoi_base_piscine(str, base);
        

        printf("\nResultado funcional:\n");
        printf("  ft_atoi_base piscine: %d\n", a);

        int b = ft_atoi_base(str, base);
        printf("  ft_atoi_base asm:  %d\n", b);
        printf("  Resultado:     %s\n",
               (a == b ? "OK" : "FAIL"));

        /* --- Benchmark --- */
        const int N = 300000;  // 300k iteraciones
        struct timespec t1, t2;

        // Benchmark ft_atoi_base_piscine
        clock_gettime(CLOCK_MONOTONIC, &t1);
        for (int i = 0; i < N; i++)
            ft_atoi_base_piscine(str, base);
        clock_gettime(CLOCK_MONOTONIC, &t2);
        long time_ref = ns_diff(t1, t2);

        // Benchmark ft_atoi_base
        clock_gettime(CLOCK_MONOTONIC, &t1);
        for (int i = 0; i < N; i++)
            ft_atoi_base(str, base);
        clock_gettime(CLOCK_MONOTONIC, &t2);
        long time_ft = ns_diff(t1, t2);

        printf("\nBenchmark (%d iteraciones):\n", N);
        printf("  ft_atoi_base piscine: %ld ns\n", time_ref);
        printf("  ft_atoi_base asm:  %ld ns\n", time_ft);

        double ratio = (double)time_ft / (double)time_ref;
        printf("  Relación:      ft_atoi_base asm es %.2fx %s\n\n",
               ratio < 1.0 ? 1.0 / ratio :  ratio,
               ratio < 1.0 ? "más rápido" : "más lento");
    }
}
