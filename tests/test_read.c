#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include "libasm.h"

void test_read(void)
{
    printf("\n--- TEST ft_read ---\n");

    char buf[20];

    printf("Escribe 5 caracteres: ");
    int r = ft_read(0, buf, 5);
    buf[r] = 0;

    printf("Leído: \"%s\"\n", buf);

    errno = 0;
    r = ft_read(-1, buf, 5);

    printf("ft_read(-1) devuelve: %d\n", r);
    printf("errno = %d (esperado: %d)\n\n", errno, EBADF);
}
