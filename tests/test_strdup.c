#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libasm.h"

void test_strdup(void)
{
    printf("\n--- TEST ft_strdup ---\n");

    char *s = "Duplicado!";
    char *a = strdup(s);
    char *b = ft_strdup(s);

    printf("strdup:    %s\n", a);
    printf("ft_strdup: %s\n", b);
    printf("Resultado: %s\n\n", strcmp(a, b) == 0 ? "OK" : "FAIL");

    free(a);
    free(b);
}
