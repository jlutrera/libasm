# ===========================
#        CONFIGURACIÓN
# ===========================

NAME	    = 	libasm.a
SRCS		= 	$(wildcard *.s)
OBJS      	= 	$(SRCS:.s=.o)
NASM        = 	nasm -f elf64

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

all			: 	$(NAME)

%.o			: 	%.s
				@echo "$(BLUE)[ASM]$(RESET) Compilando $<"
				@$(NASM) $< -o $@

$(NAME)		:	$(OBJS)
				@ar rcs $(NAME) $(OBJS)
				@echo "$(GREEN)[OK]$(RESET) Librería creada: $(NAME)"

clean		:
				@rm -f $(OBJS)
				@echo "$(YELLOW)[CLEAN]$(RESET) Objetos eliminados"

fclean		:	clean
				@rm -f $(NAME) 
				@echo "$(RED)[FCLEAN]$(RESET) Librerías eliminadas"

re			:	fclean all

# ===========================
#          PHONY
# ===========================

.PHONY		:	all clean fclean re
