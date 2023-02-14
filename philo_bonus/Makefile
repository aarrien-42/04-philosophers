# Normbre del ejecutable
NAME = philo_bonus

# Directorios
SRC_DIR = srcs/
OBJ_DIR = objs/

OBJF = objs
INC = incs

# Ficheros
SRC_FILES = main utils philo
SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

# Comandos
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -pthread #-fsanitize=address -g3
RM = rm -f
AR = ar rcs

.SILENT:

# REGLAS #
all: $(NAME)

# Compilar conjuntamente
$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "philosophers compiled!"

# Compilar objetos individualmente
$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJF)
	@echo "Compiling: $<"
	@$(CC) $(CFLAGS) -I $(INC) -c $< -o $@

# Crear directorio temporal para los obj
$(OBJF):
	@mkdir -p $(OBJ_DIR)

# Eliminar temporales
clean:
	@$(RM) -r $(OBJ_DIR)
	@echo "Objects and directory cleaned!"

# Eliminar temporales y ejecutable
fclean: clean
	@$(RM) $(NAME) libft.a
	@echo "Executable cleaned!"

re: fclean all

norm:
	@norminette $(SRC_DIR) $(INC)

.PHONY: all clean fclean re
