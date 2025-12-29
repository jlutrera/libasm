#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "libasm.h"

static long ns_diff(struct timespec a, struct timespec b)
{
    return (b.tv_sec - a.tv_sec) * 1000000000L + (b.tv_nsec - a.tv_nsec);
}

void test_strcpy(void)
{
    printf("\n--- TEST INTERACTIVO ft_strcpy + BENCHMARK ---\n");
    printf("Introduce cadenas para copiar con strcpy() y ft_strcpy().\n");
    printf("Escribe \"exit\" para salir.\n\n");

    char buffer[2048];
    char dst1[2048];
    char dst2[2048];

    while (1)
    {
        printf("Input: ");
        fflush(stdout);

        if (!fgets(buffer, sizeof(buffer), stdin))
        {
            printf("Error leyendo input.\n");
            break;
        }

        buffer[strcspn(buffer, "\n")] = '\0';

        if (strcmp(buffer, "exit") == 0)
            break;

        /* --- Comparación funcional --- */
        strcpy(dst1, buffer);
        ft_strcpy(dst2, buffer);

        printf("\nResultado funcional:\n");
        printf("  strcpy:    \"%s\"\n", dst1);
        printf("  ft_strcpy: \"%s\"\n", dst2);
        printf("  Resultado: %s\n",
               strcmp(dst1, dst2) == 0 ? "OK" : "FAIL");

        /* --- Benchmark --- */
        const int N = 2000000;  // 2 millones de iteraciones
        struct timespec t1, t2;

        // strcpy benchmark
        clock_gettime(CLOCK_MONOTONIC, &t1);
        for (int i = 0; i < N; i++)
            strcpy(dst1, buffer);
        clock_gettime(CLOCK_MONOTONIC, &t2);
        long time_strcpy = ns_diff(t1, t2);

        // ft_strcpy benchmark
        clock_gettime(CLOCK_MONOTONIC, &t1);
        for (int i = 0; i < N; i++)
            ft_strcpy(dst2, buffer);
        clock_gettime(CLOCK_MONOTONIC, &t2);
        long time_ft = ns_diff(t1, t2);

        printf("\nBenchmark (%d iteraciones):\n", N);
        printf("  strcpy:    %ld ns\n", time_strcpy);
        printf("  ft_strcpy: %ld ns\n", time_ft);

        double ratio = (double)time_ft / (double)time_strcpy;
        printf("  Relación:  ft_strcpy es %.2fx %s\n\n",
               ratio < 1.0 ? 1.0 / ratio : ratio,
               ratio < 1.0 ? "más rápido" : "más lento");
    }
}
