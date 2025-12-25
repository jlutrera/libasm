#include <stdio.h>
#include <string.h>
#include "libasm.h"

void test_strcpy(void)
{
    printf("\n--- TEST ft_strcpy ---\n");

    char dst1[100];
    char dst2[100];
    char *src = "Copilot42";

    strcpy(dst1, src);
    ft_strcpy(dst2, src);

    printf("strcpy:    %s\n", dst1);
    printf("ft_strcpy: %s\n", dst2);
    printf("Resultado: %s\n\n", strcmp(dst1, dst2) == 0 ? "OK" : "FAIL");
}
