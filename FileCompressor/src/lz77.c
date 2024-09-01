// lz77.c

#include "lz77.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definiciones y estructuras de datos

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

// Funciones para LZ77
void lz77_compress(const char *input_filename, const char *output_filename);
void lz77_decompress(const char *input_filename, const char *output_filename);

// Funciones auxiliares
static void lz77_init(LZ77Context *context);
static void slide_window(LZ77Context *context);
static LZ77Token find_longest_match(LZ77Context *context);
static void write_token(FILE *output, LZ77Token token);
static LZ77Token read_token(FILE *input);

// Inicializa el contexto LZ77
void lz77_init(LZ77Context *context) {
    if (!context) {
        fprintf(stderr, "Error: Contexto LZ77 nulo.\n");
        exit(EXIT_FAILURE);
    }

    // Inicializar la ventana deslizante y el buffer de anticipación
    memset(context->window, 0, WINDOW_SIZE);
    memset(context->lookahead_buffer, 0, LOOKAHEAD_BUFFER_SIZE);

    context->window_pos = 0;
    context->buffer_pos = 0;
}

// Encuentra la coincidencia más larga en la ventana deslizante
static LZ77Token find_longest_match(LZ77Context *context) {
    LZ77Token best_token = {0, 0, context->lookahead_buffer[0]};
    size_t i, j;
    
    for (i = 0; i < WINDOW_SIZE; ++i) {
        if (context->window[i] == context->lookahead_buffer[0]) {
            size_t length = 0;
            while (length < LOOKAHEAD_BUFFER_SIZE - 1 &&
                   i + length < WINDOW_SIZE &&
                   context->window[i + length] == context->lookahead_buffer[length]) {
                ++length;
            }

            if (length > best_token.length) {
                best_token.offset = (unsigned int)(context->window_pos - i);
                best_token.length = (unsigned int)length;
                best_token.next_char = context->lookahead_buffer[length];
            }
        }
    }
    
    return best_token;
}

// Desliza la ventana deslizante y el buffer de anticipación
static void slide_window(LZ77Context *context) {
    memmove(context->window, context->window + LOOKAHEAD_BUFFER_SIZE,
            WINDOW_SIZE - LOOKAHEAD_BUFFER_SIZE);
    memcpy(context->window + (WINDOW_SIZE - LOOKAHEAD_BUFFER_SIZE),
           context->lookahead_buffer, LOOKAHEAD_BUFFER_SIZE);

    context->window_pos = (context->window_pos + LOOKAHEAD_BUFFER_SIZE) % WINDOW_SIZE;
    context->buffer_pos = 0;
}

// Compresión de archivos usando LZ77
void lz77_compress(const char *input_filename, const char *output_filename) {
    FILE *input = fopen(input_filename, "rb");
    FILE *output = fopen(output_filename, "wb");
    LZ77Context context;
    
    if (!input || !output) {
        perror("Error al abrir archivos");
        exit(EXIT_FAILURE);
    }

    lz77_init(&context);
    
    // Leer el archivo y comprimir
    size_t bytes_read;
    while ((bytes_read = fread(context.lookahead_buffer, 1, LOOKAHEAD_BUFFER_SIZE, input)) > 0) {
        LZ77Token token = find_longest_match(&context);
        write_token(output, token);
        slide_window(&context);
    }

    fclose(input);
    fclose(output);
}

// Función para escribir un token en el archivo comprimido
static void write_token(FILE *output, LZ77Token token) {
    fwrite(&token.offset, sizeof(token.offset), 1, output);
    fwrite(&token.length, sizeof(token.length), 1, output);
    fwrite(&token.next_char, sizeof(token.next_char), 1, output);
}

// lz77.c

// Descompresión de archivos usando LZ77
void lz77_decompress(const char *input_filename, const char *output_filename) {
    FILE *input = fopen(input_filename, "rb");
    FILE *output = fopen(output_filename, "wb");
    LZ77Context context;
    LZ77Token token;

    if (!input || !output) {
        perror("Error al abrir archivos");
        exit(EXIT_FAILURE);
    }

    lz77_init(&context);

    // Leer tokens y reconstruir el archivo
    while (fread(&token, sizeof(LZ77Token), 1, input) == 1) {
        // Recuperar datos desde la ventana deslizante
        size_t start = (context.window_pos - token.offset + WINDOW_SIZE) % WINDOW_SIZE;
        size_t length = token.length;

        // Escribir los datos recuperados al archivo de salida
        for (size_t i = 0; i < length; ++i) {
            fputc(context.window[(start + i) % WINDOW_SIZE], output);
        }
        fputc(token.next_char, output);

        // Deslizar la ventana deslizante y el buffer de anticipación
        size_t pos = (context.window_pos + length + 1) % WINDOW_SIZE;
        while (context.buffer_pos < LOOKAHEAD_BUFFER_SIZE && pos < WINDOW_SIZE) {
            context.window[pos] = fgetc(input);
            if (context.window[pos] == EOF) break;
            pos = (pos + 1) % WINDOW_SIZE;
        }
        context.window_pos = (context.window_pos + length + 1) % WINDOW_SIZE;
        context.buffer_pos = 0;
    }

    fclose(input);
    fclose(output);
}

// lz77.c

// Limpieza del contexto LZ77
void lz77_cleanup(LZ77Context *context) {
    if (!context) return;
    // No se utiliza memoria dinámica en esta implementación,
    // por lo tanto, no es necesario liberar memoria.
}

// Función auxiliar para encontrar la coincidencia más larga
static LZ77Token find_longest_match(LZ77Context *context) {
    LZ77Token best_token = {0, 0, context->lookahead_buffer[0]};
    size_t i, j;

    for (i = 0; i < WINDOW_SIZE; ++i) {
        if (context->window[i] == context->lookahead_buffer[0]) {
            size_t length = 0;
            while (length < LOOKAHEAD_BUFFER_SIZE - 1 &&
                   i + length < WINDOW_SIZE &&
                   context->window[i + length] == context->lookahead_buffer[length]) {
                ++length;
            }

            if (length > best_token.length) {
                best_token.offset = (unsigned int)(context->window_pos - i);
                best_token.length = (unsigned int)length;
                best_token.next_char = context->lookahead_buffer[length];
            }
        }
    }

    return best_token;
}

// Función auxiliar para deslizar la ventana deslizante y el buffer de anticipación
static void slide_window(LZ77Context *context) {
    memmove(context->window, context->window + LOOKAHEAD_BUFFER_SIZE,
            WINDOW_SIZE - LOOKAHEAD_BUFFER_SIZE);
    memcpy(context->window + (WINDOW_SIZE - LOOKAHEAD_BUFFER_SIZE),
           context->lookahead_buffer, LOOKAHEAD_BUFFER_SIZE);

    context->window_pos = (context->window_pos + LOOKAHEAD_BUFFER_SIZE) % WINDOW_SIZE;
    context->buffer_pos = 0;
}

// Función auxiliar para escribir un token en el archivo comprimido
static void write_token(FILE *output, LZ77Token token) {
    fwrite(&token.offset, sizeof(token.offset), 1, output);
    fwrite(&token.length, sizeof(token.length), 1, output);
    fwrite(&token.next_char, sizeof(token.next_char), 1, output);
}

// Función auxiliar para leer un token desde el archivo comprimido
static LZ77Token read_token(FILE *input) {
    LZ77Token token;
    fread(&token.offset, sizeof(token.offset), 1, input);
    fread(&token.length, sizeof(token.length), 1, input);
    fread(&token.next_char, sizeof(token.next_char), 1, input);
    return token;
}
