#ifndef CONFIG_H
#define CONFIG_H

// Parámetros de Compresión

// Tamaño máximo de la tabla de frecuencias para el algoritmo Huffman
#define HUFFMAN_MAX_TABLE_SIZE 256 // Ajustar según el rango de valores posibles en el dataset

// Tamaño máximo de la tabla de códigos para el algoritmo Huffman
#define HUFFMAN_MAX_CODE_SIZE 256 // Ajustar para el número máximo de códigos posibles

// Tamaño máximo de la ventana de búsqueda para el algoritmo LZ77
#define LZ77_MAX_WINDOW_SIZE 32768 // Ajustar según la memoria disponible

// Tamaño máximo de los patrones para el algoritmo LZ77
#define LZ77_MAX_PATTERN_SIZE 258 // Ajustar para el tamaño máximo de los patrones encontrados

// Configurar Tamaños de Buffers

// Tamaño del buffer de entrada
#define INPUT_BUFFER_SIZE 8192 // Ajustar para el tamaño adecuado de los datos de entrada

// Tamaño del buffer de salida
#define OUTPUT_BUFFER_SIZE 8192 // Ajustar para el tamaño adecuado de los datos de salida

// Definir Opciones de Depuración

// Habilitar mensajes de depuración (0 deshabilitado, 1 habilitado)
#define DEBUG_MODE 1 // Cambiar a 0 para deshabilitar mensajes de depuración

// Configurar Parámetros Generales del Proyecto

// Número máximo de archivos que se pueden procesar simultáneamente
#define MAX_CONCURRENT_FILES 10 // Ajustar según las necesidades del proyecto

// Tamaño máximo de un archivo comprimido (en bytes)
#define MAX_COMPRESSED_FILE_SIZE (1024 * 1024 * 100) // 100 MB, ajustar según el tamaño máximo esperado

#endif // UTILS_CONFIG_H
