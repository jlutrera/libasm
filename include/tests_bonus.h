#ifndef TESTS_BONUS_H
# define TESTS_BONUS_H

/* Colores ANSI */
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define RESET   "\033[0m"

/* The linked list function will use the following structure */
typedef struct  s_list
{
    void *data;
    struct s_list *next;
}               t_list;

/* Bonus tests */
void    test_atoi_base(void);
void    test_list_push_front(void);
void    test_list_size(void);
void    test_list_sort(void);
void    test_list_remove_if(void);

#endif