#ifndef TESTS_H
# define TESTS_H

/* Colores ANSI */
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define RESET   "\033[0m"

/* Mandatory tests */
void    test_strlen(void);
void    test_strcpy(void);
void    test_strcmp(void);
void    test_write(void);
void    test_read(void);
void    test_strdup(void);

#endif
