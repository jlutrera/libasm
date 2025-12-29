#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include "libasm.h"

volatile ssize_t sink_read;

static long ns_diff(struct timespec a, struct timespec b)
{
    return (b.tv_sec - a.tv_sec) * 1000000000L + (b.tv_nsec - a.tv_nsec);
}

void test_read(void)
{
    char buf[1024];

    printf("\n=== TEST INTERACTIVO ft_read + BENCHMARK ===\n");
    printf("Escribe texto para leer con ft_read() y read().\n");
    printf("Escribe \"exit\" para salir.\n\n");

    while (1)
    {
        printf("Input con ft_read(): ");
        fflush(stdout);

        errno = 0;
        ssize_t ret1 = ft_read(0, buf, sizeof(buf) - 1);
        int e1 = errno;

        if (ret1 < 0)
            buf[0] = '\0';
        else
        {
            // Eliminar salto de línea si existe
            if (ret1 > 0 && buf[ret1 - 1] == '\n')
                buf[ret1 - 1] = '\0';
            else
                buf[ret1] = '\0';
        }

        // Comando de salida
        if (strcmp(buf, "exit") == 0)
            break;

        printf("\n  ret = %zd\n  errno = %d (%s)\n  buffer = \"%s\"\n",
               ret1, e1, strerror(e1), buf);

        /* --- Comparación con read() --- */
        printf("\nInput con read(): ");
        fflush(stdout);

        errno = 0;
        ssize_t ret2 = read(0, buf, sizeof(buf) - 1);
        int e2 = errno;

        if (ret2 < 0)
            buf[0] = '\0';
        else
        {
            if (ret2 > 0 && buf[ret2 - 1] == '\n')
                buf[ret2 - 1] = '\0';
            else
                buf[ret2] = '\0';
        }

        printf("\n  ret = %zd\n  errno = %d (%s)\n  buffer = \"%s\"\n",
               ret2, e2, strerror(e2), buf);

        printf("\nResultado lectura stdin: %s\n",
               (ret1 == ret2 && e1 == e2 ? "OK" : "FAIL"));

        /* --- Test de error --- */
        printf("\n--- Test de error (fd = -1) ---\n");

        errno = 0;
        ret1 = ft_read(-1, buf, 10);
        e1 = errno;

        errno = 0;
        ret2 = read(-1, buf, 10);
        e2 = errno;

        printf("  ft_read(-1) → ret = %zd, errno = %d (%s)\n",
               ret1, e1, strerror(e1));
        printf("  read(-1)    → ret = %zd, errno = %d (%s)\n",
               ret2, e2, strerror(e2));
        printf("  Resultado: %s\n",
               (ret1 == ret2 && e1 == e2 ? "OK" : "FAIL"));

        /* --- Benchmark --- */
        printf("\n--- Benchmark leyendo de /dev/zero ---\n");

        int devzero = open("/dev/zero", O_RDONLY);
        if (devzero < 0)
        {
            perror("open /dev/zero");
            return;
        }

        char bench_buf[4096];
        const int N = 500000;
        struct timespec t1, t2;

        clock_gettime(CLOCK_MONOTONIC, &t1);
        for (int i = 0; i < N; i++)
            sink_read = read(devzero, bench_buf, sizeof(bench_buf));
        clock_gettime(CLOCK_MONOTONIC, &t2);
        long time_read = ns_diff(t1, t2);

        clock_gettime(CLOCK_MONOTONIC, &t1);
        for (int i = 0; i < N; i++)
            sink_read = ft_read(devzero, bench_buf, sizeof(bench_buf));
        clock_gettime(CLOCK_MONOTONIC, &t2);
        long time_ft = ns_diff(t1, t2);

        close(devzero);

        printf("  read:    %ld ns\n", time_read);
        printf("  ft_read: %ld ns\n", time_ft);

        double ratio = (double)time_ft / (double)time_read;
        printf("  Relación: ft_read es %.2fx %s\n\n",
               ratio < 1.0 ? 1.0 / ratio : ratio,
               ratio < 1.0 ? "más rápido" : "más lento");
    }
}
