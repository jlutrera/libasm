#include <stdio.h>
#include <string.h>
#include "libasm_bonus.h"

/* ---------------------------------------------------------
   Test interactivo + benchmark
   --------------------------------------------------------- */
void test_atoi_base(void)
{
    printf("\n=== TEST INTERACTIVO ft_atoi_base ===\n");
    printf("Introduce una cadena y una base para convertir.\n");
    printf("Escribe \"exit\" en cualquiera de los campos para salir.\n\n");

    char str[256];
    char base[256];

    while (1)
    {
        printf("Cadena: ");
        fflush(stdout);

        if (!fgets(str, sizeof(str), stdin))
            break;

        str[strcspn(str, "\n")] = '\0';
        if (strcmp(str, "exit") == 0)
            break;

        printf("Base:   ");
        fflush(stdout);

        if (!fgets(base, sizeof(base), stdin))
            break;

        base[strcspn(base, "\n")] = '\0';
        if (strcmp(base, "exit") == 0)
            break;

        int a = ft_atoi_base(str, base);
        printf("  Resultado:  %d\n", a);
	}
}
