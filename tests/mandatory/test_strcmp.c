#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "libasm.h"

volatile int sink_strcmp;   // evita optimización del compilador

static long ns_diff(struct timespec a, struct timespec b)
{
    return (b.tv_sec - a.tv_sec) * 1000000000L + (b.tv_nsec - a.tv_nsec);
}

void test_strcmp(void)
{
    printf("\n--- TEST INTERACTIVO ft_strcmp + BENCHMARK ---\n");
    printf("Introduce dos cadenas para comparar strcmp() y ft_strcmp().\n");
    printf("Escribe \"exit\" para salir.\n\n");

    char s1[1024];
    char s2[1024];

    while (1)
    {
        printf("Cadena 1: ");
        fflush(stdout);
        if (!fgets(s1, sizeof(s1), stdin))
        {
            printf("Error leyendo input.\n");
            break;
        }
        s1[strcspn(s1, "\n")] = '\0';

        if (strcmp(s1, "exit") == 0)
            break;

        printf("Cadena 2: ");
        fflush(stdout);
        if (!fgets(s2, sizeof(s2), stdin))
        {
            printf("Error leyendo input.\n");
            break;
        }
        s2[strcspn(s2, "\n")] = '\0';

        if (strcmp(s2, "exit") == 0)
        {
            printf("Saliendo del test...\n");
            break;
        }

        /* --- Comparación funcional --- */
        int c1 = strcmp(s1, s2);
        int c2 = ft_strcmp(s1, s2);

        printf("\nResultado funcional:\n");
        printf("  strcmp:    %d\n", c1);
        printf("  ft_strcmp: %d\n", c2);
        printf("  Resultado: %s\n",
               (c1 == c2 ? "OK" : "FAIL"));

        /* --- Benchmark --- */
        const int N = 3000000;
        struct timespec t1, t2;

        // Benchmark strcmp
        clock_gettime(CLOCK_MONOTONIC, &t1);
        for (int i = 0; i < N; i++)
            sink_strcmp = strcmp(s1, s2);
        clock_gettime(CLOCK_MONOTONIC, &t2);
        long time_str = ns_diff(t1, t2);

        // Benchmark ft_strcmp
        clock_gettime(CLOCK_MONOTONIC, &t1);
        for (int i = 0; i < N; i++)
            sink_strcmp = ft_strcmp(s1, s2);
        clock_gettime(CLOCK_MONOTONIC, &t2);
        long time_ft = ns_diff(t1, t2);

        printf("\nBenchmark (%d iteraciones):\n", N);
        printf("  strcmp:    %ld ns\n", time_str);
        printf("  ft_strcmp: %ld ns\n", time_ft);

        double ratio = (double)time_ft / (double)time_str;
        printf("  Relación:  ft_strcmp es %.2fx %s\n\n",
               ratio < 1.0 ? 1.0 / ratio : ratio,
               ratio < 1.0 ? "más rápido" : "más lento");
    }
}
