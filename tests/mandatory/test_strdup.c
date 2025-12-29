#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "libasm.h"

volatile char *sink_strdup;   // evita optimización del compilador

static long ns_diff(struct timespec a, struct timespec b)
{
    return (b.tv_sec - a.tv_sec) * 1000000000L + (b.tv_nsec - a.tv_nsec);
}

void test_strdup(void)
{
    printf("\n=== TEST INTERACTIVO ft_strdup + BENCHMARK ===\n");
    printf("Introduce cadenas para duplicar con strdup() y ft_strdup().\n");
    printf("Escribe \"exit\" para salir.\n\n");

    char buffer[2048];

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
        char *a = strdup(buffer);
        char *b = ft_strdup(buffer);

        printf("\nResultado funcional:\n");
        printf("  strdup:    \"%s\"\n", a);
        printf("  ft_strdup: \"%s\"\n", b);
        printf("  Resultado: %s\n",
               (strcmp(a, b) == 0 ? "OK" : "FAIL"));

        /* --- Benchmark --- */
        const int N = 500000;  // medio millón de duplicaciones
        struct timespec t1, t2;

        // Benchmark strdup
        clock_gettime(CLOCK_MONOTONIC, &t1);
        for (int i = 0; i < N; i++)
        {
            sink_strdup = strdup(buffer);
            free((void *)sink_strdup);
        }
        clock_gettime(CLOCK_MONOTONIC, &t2);
        long time_std = ns_diff(t1, t2);

        // Benchmark ft_strdup
        clock_gettime(CLOCK_MONOTONIC, &t1);
        for (int i = 0; i < N; i++)
        {
            sink_strdup = ft_strdup(buffer);
            free((void *)sink_strdup);
        }
        clock_gettime(CLOCK_MONOTONIC, &t2);
        long time_ft = ns_diff(t1, t2);

        printf("\nBenchmark (%d iteraciones):\n", N);
        printf("  strdup:    %ld ns\n", time_std);
        printf("  ft_strdup: %ld ns\n", time_ft);

        double ratio = (double)time_ft / (double)time_std;
        printf("  Relación:  ft_strdup es %.2fx %s\n\n",
               ratio < 1.0 ? 1.0 / ratio : ratio,
               ratio < 1.0 ? "más rápido" : "más lento");

        free(a);
        free(b);
    }
}
