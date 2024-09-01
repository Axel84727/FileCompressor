// lz77.h

#ifndef LZ77_H
#define LZ77_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

// Definiciones de constantes
#define WINDOW_SIZE 4096        // Tamaño de la ventana deslizante
#define LOOKAHEAD_BUFFER_SIZE 18 // Tamaño del buffer de anticipación
#define MAX_MATCH_LENGTH (LOOKAHEAD_BUFFER_SIZE - 1) // Longitud máxima de coincidencia

// Estructura para almacenar un par de desplazamiento y longitud
typedef struct {
    unsigned int offset; // Desplazamiento dentro de la ventana
    unsigned int length; // Longitud de la coincidencia
    char next_char;      // Siguiente carácter después de la coincidencia
} LZ77Token;

// Estructura para la ventana deslizante y buffer de anticipación
typedef struct {
    unsigned char window[WINDOW_SIZE];        // Ventana deslizante
    unsigned char lookahead_buffer[LOOKAHEAD_BUFFER_SIZE]; // Buffer de anticipación
    size_t window_pos; // Posición actual en la ventana deslizante
    size_t buffer_pos; // Posición actual en el buffer de anticipación
} LZ77Context;

// Declaración de funciones para LZ77
/**
 * Comprime un archivo utilizando el algoritmo LZ77.
 *
 * @param input_filename Nombre del archivo de entrada a comprimir.
 * @param output_filename Nombre del archivo de salida comprimido.
 */
void lz77_compress(const char *input_filename, const char *output_filename);

/**
 * Descomprime un archivo comprimido utilizando el algoritmo LZ77.
 *
 * @param input_filename Nombre del archivo comprimido a descomprimir.
 * @param output_filename Nombre del archivo de salida descomprimido.
 */
void lz77_decompress(const char *input_filename, const char *output_filename);

/**
 * Inicializa el contexto LZ77.
 *
 * @param context Puntero al contexto LZ77 a inicializar.
 */
void lz77_init(LZ77Context *context);

/**
 * Limpia el contexto LZ77.
 *
 * @param context Puntero al contexto LZ77 a limpiar.
 */
void lz77_cleanup(LZ77Context *context);

// Funciones auxiliares (privadas en lz77.c)
/**
 * Desliza la ventana deslizante y el buffer de anticipación.
 *
 * @param context Puntero al contexto LZ77 a actualizar.
 */
static void slide_window(LZ77Context *context);

/**
 * Encuentra la coincidencia más larga en la ventana deslizante.
 *
 * @param context Puntero al contexto LZ77 a usar.
 * @return Token con la mejor coincidencia encontrada.
 */
static LZ77Token find_longest_match(LZ77Context *context);

/**
 * Escribe un token en el archivo de salida.
 *
 * @param output Puntero al archivo de salida.
 * @param token Token a escribir.
 */
static void write_token(FILE *output, LZ77Token token);

/**
 * Lee un token desde el archivo de entrada.
 *
 * @param input Puntero al archivo de entrada.
 * @return Token leído.
 */
static LZ77Token read_token(FILE *input);

#endif // LZ77_H
