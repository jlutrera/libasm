#include <stdio.h>
#include "libasm.h"

void test_atoi_base(void)
{
    printf("\n--- TEST ft_atoi_base ---\n");

    printf("ft_atoi_base(\"1010\", \"01\") = %d (esperado 10)\n",
        ft_atoi_base("1010", "01"));

    printf("ft_atoi_base(\"A\", \"ABCDEF\") = %d (esperado 0)\n",
        ft_atoi_base("A", "ABCDEF"));

    printf("ft_atoi_base(\"  -1A\", \"0123456789ABCDEF\") = %d (esperado -26)\n",
        ft_atoi_base("  -1A", "0123456789ABCDEF"));

    printf("\n");
}
