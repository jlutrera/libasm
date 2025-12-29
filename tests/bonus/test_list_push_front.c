#include <stdio.h>
#include <stdlib.h>
#include "libasm_bonus.h"

void test_list_push_front(void)
{
    printf("\n--- TEST ft_list_push_front ---\n");

    t_list *lst = NULL;

    ft_list_push_front(&lst, "c");
    ft_list_push_front(&lst, "b");
    ft_list_push_front(&lst, "a");

    for (t_list *p = lst; p; p = p->next)
        printf("Nodo: %s\n", (char *)p->data);

    printf("\n");
}
