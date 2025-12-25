#include <stdio.h>
#include <string.h>
#include "libasm.h"

void test_strlen(void)
{
    printf("\n--- TEST ft_strlen ---\n");

    char *tests[] = {"", "Hola", "42Madrid", "ABCDEFGHIJK", NULL};

    for (int i = 0; tests[i]; i++)
    {
        size_t a = strlen(tests[i]);
        size_t b = ft_strlen(tests[i]);

        printf("Test %d: \"%s\"\n", i, tests[i]);
        printf("  strlen    = %zu\n", a);
        printf("  ft_strlen = %zu\n", b);
        printf("  Resultado = %s\n\n", (a == b ? "OK" : "FAIL"));
    }
}
