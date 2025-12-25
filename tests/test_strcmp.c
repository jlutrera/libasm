#include <stdio.h>
#include <string.h>
#include "libasm.h"

void test_strcmp(void)
{
    printf("\n--- TEST ft_strcmp ---\n");

    char *a[] = {"abc", "abc", "abc", "xyz", "hola", NULL};
    char *b[] = {"abc", "abd", "abcd", "xyz", "holb", NULL};

    for (int i = 0; a[i]; i++)
    {
        int s1 = strcmp(a[i], b[i]);
        int s2 = ft_strcmp(a[i], b[i]);

        printf("Test %d: \"%s\" vs \"%s\"\n", i, a[i], b[i]);
        printf("  strcmp    = %d\n", s1);
        printf("  ft_strcmp = %d\n", s2);
        printf("  Resultado = %s\n\n", (s1 == s2 ? "OK" : "FAIL"));
    }
}
