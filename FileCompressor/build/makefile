# 1. Definir Variables
CC = gcc                            # Compilador
CFLAGS = -Wall -Wextra -O2          # Flags de compilación
LDFLAGS =                           # Flags de enlace
SRC_DIR = src                        # Directorio de código fuente
OBJ_DIR = obj                        # Directorio de objetos
BIN_DIR = bin                        # Directorio de binarios
EXEC = $(BIN_DIR)/compressor         # Nombre del ejecutable

# 2. Listar Archivos Fuentes
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)       # Archivos fuente en SRC_DIR
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))  # Archivos objeto correspondientes

# 3. Reglas de Construcción

# Regla principal
all: $(EXEC)

# Regla para compilar archivos .c en archivos .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)                # Crea el directorio de objetos si no existe
	$(CC) $(CFLAGS) -c $< -o $@

# Regla para enlazar archivos objeto y crear el ejecutable
$(EXEC): $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)                # Crea el directorio de binarios si no existe
	$(CC) $(LDFLAGS) $^ -o $@

# Regla para limpiar archivos objeto y ejecutables
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Reglas Adicionales

# Regla para recompilar automáticamente si los archivos de cabecera cambian
rebuild: clean all

# Regla de instalación (opcional)
install: all
	cp $(EXEC) /usr/local/bin/$(EXEC)

# 5. Variables de Configuración
DEBUG_FLAGS = -g                     # Flags para compilación de depuración

# 6. Documentación
# Este Makefile compila un proyecto de compresión de archivos.
# Comandos:
#   make        - Compila el proyecto.
#   make clean  - Elimina archivos objeto y binarios.
#   make rebuild - Limpia y recompila el proyecto.
#   make install - Instala el ejecutable en /usr/local/bin/
