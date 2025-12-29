#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "libasm.h"

volatile size_t sink_strlen;

static long ns_diff(struct timespec a, struct timespec b)
{
    return (b.tv_sec - a.tv_sec) * 1000000000L + (b.tv_nsec - a.tv_nsec);
}

void test_strlen(void)
{
    printf("\n--- TEST INTERACTIVO ft_strlen + BENCHMARK ---\n");
    printf("Introduce cadenas para comparar strlen() y ft_strlen().\n");
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

        // Eliminar salto de línea
        buffer[strcspn(buffer, "\n")] = '\0';

        // Comando de salida
        if (strcmp(buffer, "exit") == 0)
        {
            printf("Saliendo del test...\n");
            break;
        }

        /* --- Comparación funcional --- */
        size_t a = strlen(buffer);
        size_t b = ft_strlen(buffer);

        printf("\nResultado funcional:\n");
        printf("  strlen:    %zu\n", a);
        printf("  ft_strlen: %zu\n", b);
        printf("  Resultado: %s\n",
               (a == b ? "OK" : "FAIL"));

        /* --- Benchmark --- */
        const int N = 3000000;  // 3 millones de iteraciones
        struct timespec t1, t2;

        // Benchmark strlen
        clock_gettime(CLOCK_MONOTONIC, &t1);
        for (int i = 0; i < N; i++)
            sink_strlen = strlen(buffer);
        clock_gettime(CLOCK_MONOTONIC, &t2);
        long time_str = ns_diff(t1, t2);

        // Benchmark ft_strlen
        clock_gettime(CLOCK_MONOTONIC, &t1);
        for (int i = 0; i < N; i++)
            sink_strlen = ft_strlen(buffer);
        clock_gettime(CLOCK_MONOTONIC, &t2);
        long time_ft = ns_diff(t1, t2);

        printf("\nBenchmark (%d iteraciones):\n", N);
        printf("  strlen:    %ld ns\n", time_str);
        printf("  ft_strlen: %ld ns\n", time_ft);

        double ratio = (double)time_ft / (double)time_str;
        printf("  Relación:  ft_strlen es %.2fx %s\n\n",
               ratio < 1.0 ? 1.0 / ratio : ratio,
               ratio < 1.0 ? "más rápido" : "más lento");
    }
}
