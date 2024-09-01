#!/bin/bash

# 1. Definir el Intérprete
# (Ya definido arriba con #!/bin/bash)

# 2. Configurar Variables de Entorno
PROJECT_DIR=$(pwd)               # Directorio del proyecto actual
COMPILER=gcc                     # Compilador a utilizar
CFLAGS="-Wall -Wextra -O2"       # Flags de compilación (warnings y optimización)
LDFLAGS=""                       # Flags de enlace (pueden incluir bibliotecas externas)
OUTPUT_EXECUTABLE=program        # Nombre del ejecutable final

# 3. Limpiar Archivos Anteriores
echo "Limpiando archivos anteriores..."
rm -f *.o *.out $OUTPUT_EXECUTABLE

# 4. Compilar Archivos Fuente
echo "Compilando archivos fuente..."
$COMPILER $CFLAGS -c *.c -o temp.o
if [ $? -ne 0 ]; then
    echo "Error durante la compilación de archivos fuente."
    exit 1
fi

# 5. Enlazar Archivos Objeto
echo "Enlazando archivos objeto..."
$COMPILER $LDFLAGS *.o -o $OUTPUT_EXECUTABLE
if [ $? -ne 0 ]; then
    echo "Error durante el enlace de archivos objeto."
    exit 1
fi

# 6. Mostrar Mensaje de Éxito
echo "Compilación exitosa: $OUTPUT_EXECUTABLE creado."

# 7. Manejar Errores
# (Manejo de errores ya incluido en la sección de compilación y enlace)
    