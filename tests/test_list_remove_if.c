#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libasm.h"

void test_list_remove_if(void)
{
    printf("\n--- TEST ft_list_remove_if ---\n");

    t_list *lst = NULL;

    ft_list_push_front(&lst, strdup("c"));
    ft_list_push_front(&lst, strdup("b"));
    ft_list_push_front(&lst, strdup("a"));

    ft_list_remove_if(&lst, "b", (int (*)())strcmp, free);

    for (t_list *p = lst; p; p = p->next)
        printf("%s\n", (char *)p->data);

    printf("\n");
}
