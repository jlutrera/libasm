# ===========================
#        CONFIGURACIÓN
# ===========================

NAME        =	main

CC          = 	gcc
CFLAGS      = 	-Wall -Wextra -Werror -Iinclude -Itests -fno-pie -no-pie

SRC_DIR     = 	srcs
TEST_DIR    = 	tests
LIBASM      = 	$(SRC_DIR)/libasm.a
TEST_SRCS   = 	$(wildcard tests/*.c)

# ===========================
#          COLORES
# ===========================

GREEN   	= 	\033[1;32m
YELLOW  	= 	\033[1;33m
BLUE    	= 	\033[1;34m
RED     	= 	\033[1;31m
RESET   	= 	\033[0m

# ===========================
#          REGLAS
# ===========================

all			: 	$(LIBASM) $(NAME)

$(LIBASM)	:
				@echo "$(BLUE)[LIBASM]$(RESET) Compilando mandatory..."
				@$(MAKE) --no-print-directory -C $(SRC_DIR)

$(NAME)		: 	$(TEST_SRCS) $(LIB)
				@echo "$(GREEN)[OK]$(RESET) Enlazando main con libasm.a"
				@$(CC) $(CFLAGS) $(TEST_SRCS) -L$(SRC_DIR) -lasm -o $(NAME)
				@echo "$(GREEN)[DONE]$(RESET) Ejecutable creado: ./main"

clean		:
				@$(MAKE) clean --no-print-directory -C $(SRC_DIR)
				@echo "$(YELLOW)[CLEAN]$(RESET) Objetos eliminados"

fclean		: 	clean
				@$(MAKE) fclean --no-print-directory -C $(SRC_DIR)
				@rm -f $(NAME)
				@echo "$(RED)[FCLEAN]$(RESET) Ejecutables eliminados"

re			: 	fclean all

# ===========================
#          PHONY
# ===========================

.PHONY		: 	all clean fclean re
