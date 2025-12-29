#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include "libasm.h"

volatile ssize_t sink_write;   // evita optimización del compilador

static long ns_diff(struct timespec a, struct timespec b)
{
    return (b.tv_sec - a.tv_sec) * 1000000000L + (b.tv_nsec - a.tv_nsec);
}

void test_write(void)
{
    printf("\n=== TEST INTERACTIVO ft_write + BENCHMARK ===\n");
    printf("Introduce texto para escribir con write() y ft_write().\n");
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
       

        size_t len = strlen(buffer);

        /* --- Comparación funcional --- */
        printf("\n--- Escribiendo en STDOUT (fd = 1) ---\n");

        errno = 0;
        ssize_t r1 = ft_write(1, buffer, len);
        int e1 = errno;

        errno = 0;
        ssize_t r2 = write(1, buffer, len);
        int e2 = errno;

        printf("\nResultados:\n");
        printf("  ft_write → ret = %zd, errno = %d (%s)\n", r1, e1, strerror(e1));
        printf("  write    → ret = %zd, errno = %d (%s)\n", r2, e2, strerror(e2));
        printf("  Resultado: %s\n",
               (r1 == r2 && e1 == e2 ? "OK" : "FAIL"));

        /* --- Error test --- */
        printf("\n--- Test de error (fd = -1) ---\n");

        errno = 0;
        r1 = ft_write(-1, buffer, len);
        e1 = errno;

        errno = 0;
        r2 = write(-1, buffer, len);
        e2 = errno;

        printf("  ft_write(-1) → ret = %zd, errno = %d (%s)\n", r1, e1, strerror(e1));
        printf("  write(-1)    → ret = %zd, errno = %d (%s)\n", r2, e2, strerror(e2));
        printf("  Resultado: %s\n",
               (r1 == r2 && e1 == e2 ? "OK" : "FAIL"));

        /* --- Benchmark escribiendo en /dev/null --- */
        printf("\n--- Benchmark escribiendo en /dev/null ---\n");

        int devnull = open("/dev/null", O_WRONLY);
        if (devnull < 0)
        {
            perror("open /dev/null");
            return;
        }

        const int N = 500000;  // medio millón de iteraciones
        struct timespec t1, t2;

        // Benchmark write
        clock_gettime(CLOCK_MONOTONIC, &t1);
        for (int i = 0; i < N; i++)
            sink_write = write(devnull, buffer, len);
        clock_gettime(CLOCK_MONOTONIC, &t2);
        long time_write = ns_diff(t1, t2);

        // Benchmark ft_write
        clock_gettime(CLOCK_MONOTONIC, &t1);
        for (int i = 0; i < N; i++)
            sink_write = ft_write(devnull, buffer, len);
        clock_gettime(CLOCK_MONOTONIC, &t2);
        long time_ft = ns_diff(t1, t2);

        close(devnull);

        printf("  write:    %ld ns\n", time_write);
        printf("  ft_write: %ld ns\n", time_ft);

        double ratio = (double)time_ft / (double)time_write;
        printf("  Relación: ft_write es %.2fx %s\n\n",
               ratio < 1.0 ? 1.0 / ratio : ratio,
               ratio < 1.0 ? "más rápido" : "más lento");
    }
}
