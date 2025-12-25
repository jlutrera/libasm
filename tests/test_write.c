#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include "libasm.h"

void test_write(void)
{
    printf("\n--- TEST ft_write ---\n");

    ft_write(1, "Probando ft_write\n", 18);

    errno = 0;
    int r = ft_write(-1, "error", 5);

    printf("ft_write(-1) devuelve: %d\n", r);
    printf("errno = %d (esperado: %d)\n\n", errno, EBADF);
}
