#include <stdio.h>
#include <stdlib.h>
#include "tests.h"

/* Limpiar pantalla */
static void clear_screen()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

/* Leer opción de menú, borrando buffer si hay más de un carácter*/
static int read_option(void)
{
    int opt;

    if (scanf("%d", &opt) != 1)
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return -1;  // entrada inválida
    }
    return opt;
}

/* Pausa */
static void wait_enter(void)
{
    printf(YELLOW "\nPress ENTER to continue..." RESET);
    getchar(); getchar();
}

/* ===========================
        MENÚ MANDATORY
   =========================== */
static void test_mandatory(void)
{
    int opt;

    while (1)
    {
        clear_screen();
        printf(BLUE "=====================================\n" RESET);
        printf(BLUE "           MANDATORY TESTS           \n" RESET);
        printf(BLUE "=====================================\n\n" RESET);

        printf("  1. ft_strlen\n");
        printf("  2. ft_strcpy\n");
        printf("  3. ft_strcmp\n");
        printf("  4. ft_write\n");
        printf("  5. ft_read\n");
        printf("  6. ft_strdup\n\n");
        printf("  0. Return\n\n");

        printf(GREEN "Select an option: " RESET);
        opt = read_option();

        switch (opt)
        {
            case 1: test_strlen(); break;
            case 2: test_strcpy(); break;
            case 3: test_strcmp(); break;
            case 4: test_write(); break;
            case 5: test_read(); break;
            case 6: test_strdup(); break;
            case 0: return;
            default: continue;
        }
        wait_enter();
    }
}

/* ===========================
           MENÚ BONUS
   =========================== */
static void test_bonus(void)
{
    int opt;

    while (1)
    {
        clear_screen();
        printf(BLUE "=====================================\n" RESET);
        printf(BLUE "              BONUS TESTS            \n" RESET);
        printf(BLUE "=====================================\n\n" RESET);

        printf("  1. ft_atoi_base\n");
        printf("  2. ft_list_push_front\n");
        printf("  3. ft_list_size\n");
        printf("  4. ft_list_sort\n");
        printf("  5. ft_list_remove_if\n\n");
        printf("  0. Return\n\n");

        printf(GREEN "Select an option: " RESET);
        opt = read_option();

        switch (opt)
        {
            case 1: test_atoi_base(); break;
            case 2: test_list_push_front(); break;
            case 3: test_list_size(); break;
            case 4: test_list_sort(); break;
            case 5: test_list_remove_if(); break;
            case 0: return;
            default: continue;
        }
        wait_enter();
    }
}

/* ===========================
              MAIN
   =========================== */
int main(void)
{
    int opt;

    while (1)
    {
        clear_screen();
        printf(BLUE "=====================================\n" RESET);
        printf(BLUE "            LIBASM TEST MENU         \n" RESET);
        printf(BLUE "=====================================\n\n" RESET);

        printf("  1. Mandatory tests\n");
        printf("  2. Bonus tests\n\n");
        printf("  0. Exit\n\n");

        printf(GREEN "Select an option: " RESET);
        opt = read_option();

        switch (opt)
        {
            case 1: test_mandatory(); break;
            case 2: test_bonus(); break;
            case 0: clear_screen();
                    printf(YELLOW "Bye!\n" RESET);
                    return 0;
            default: continue;
        }
    }
}
