#include <stdio.h>
#include <stdlib.h>
#include "libasm_bonus.h"

void test_list_size(void)
{
    printf("\n=== TEST INTERACTIVO ft_list_size ===\n");
    printf("Introduce una cadena y una base para convertir.\n");
    printf("Escribe \"exit\" en cualquiera de los campos para salir.\n\n");   

    t_list *lst = NULL;

    ft_list_push_front(&lst, "c");
    ft_list_push_front(&lst, "b");
    ft_list_push_front(&lst, "a");

    printf("size = %d (esperado 3)\n\n", ft_list_size(lst));
}
