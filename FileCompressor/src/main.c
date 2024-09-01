// src/main.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"
#include "lz77.h"
#include "file_io.h"

// Prototipos de funciones
void process_arguments(int argc, char *argv[], char **mode, char **algorithm, char **input_file, char **output_file);
void initialize_config(char **buffer, size_t *buffer_size);
void select_algorithm(const char *mode, const char *algorithm, const char *input_file, const char *output_file);
void handle_error(const char *msg);
void free_resources(char *buffer);

void compress_with_huffman(const char *input_file, const char *output_file);
void compress_with_lz77(const char *input_file, const char *output_file);
void decompress_with_huffman(const char *input_file, const char *output_file);
void decompress_with_lz77(const char *input_file, const char *output_file);

int main(int argc, char *argv[]) {
    char *mode = NULL;
    char *algorithm = NULL;
    char *input_file = NULL;
    char *output_file = NULL;

    process_arguments(argc, argv, &mode, &algorithm, &input_file, &output_file);

    // Variables de configuración y buffers
    char *buffer = NULL;
    size_t buffer_size = 0;
    initialize_config(&buffer, &buffer_size);

    // Lógica de selección de algoritmo
    select_algorithm(mode, algorithm, input_file, output_file);

    // Liberación de recursos
    free_resources(buffer);
    return 0;
}

void process_arguments(int argc, char *argv[], char **mode, char **algorithm, char **input_file, char **output_file) {
    if (argc < 5) {
        handle_error("Uso: <modo> <algoritmo> <archivo_entrada> <archivo_salida>");
    }

    *mode = argv[1];
    *algorithm = argv[2];
    *input_file = argv[3];
    *output_file = argv[4];
}

void initialize_config(char **buffer, size_t *buffer_size) {
    *buffer = NULL;
    *buffer_size = 0;
}

void select_algorithm(const char *mode, const char *algorithm, const char *input_file, const char *output_file) {
    if (strcmp(mode, "compress") == 0) {
        if (strcmp(algorithm, "huffman") == 0) {
            compress_with_huffman(input_file, output_file);
        } else if (strcmp(algorithm, "lz77") == 0) {
            compress_with_lz77(input_file, output_file);
        } else {
            handle_error("Algoritmo no soportado.");
        }
    } else if (strcmp(mode, "decompress") == 0) {
        if (strcmp(algorithm, "huffman") == 0) {
            decompress_with_huffman(input_file, output_file);
        } else if (strcmp(algorithm, "lz77") == 0) {
            decompress_with_lz77(input_file, output_file);
        } else {
            handle_error("Algoritmo no soportado.");
        }
    } else {
        handle_error("Modo no soportado.");
    }
}

void handle_error(const char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

void compress_with_huffman(const char *input_file, const char *output_file) {
    FILE *in = fopen(input_file, "rb");
    FILE *out = fopen(output_file, "wb");

    if (!in || !out) {
        handle_error("Error al abrir archivos.");
    }

    // Lógica para compresión con Huffman
    // Leer archivo de entrada, comprimir datos y escribir en archivo de salida

    fclose(in);
    fclose(out);
}

void compress_with_lz77(const char *input_file, const char *output_file) {
    FILE *in = fopen(input_file, "rb");
    FILE *out = fopen(output_file, "wb");

    if (!in || !out) {
        handle_error("Error al abrir archivos.");
    }

    // Lógica para compresión con LZ77
    // Leer archivo de entrada, comprimir datos y escribir en archivo de salida

    fclose(in);
    fclose(out);
}

void decompress_with_huffman(const char *input_file, const char *output_file) {
    FILE *in = fopen(input_file, "rb");
    FILE *out = fopen(output_file, "wb");

    if (!in || !out) {
        handle_error("Error al abrir archivos.");
    }

    // Lógica para descompresión con Huffman
    // Leer archivo de entrada, descomprimir datos y escribir en archivo de salida

    fclose(in);
    fclose(out);
}

void decompress_with_lz77(const char *input_file, const char *output_file) {
    FILE *in = fopen(input_file, "rb");
    FILE *out = fopen(output_file, "wb");

    if (!in || !out) {
        handle_error("Error al abrir archivos.");
    }

    // Lógica para descompresión con LZ77
    // Leer archivo de entrada, descomprimir datos y escribir en archivo de salida

    fclose(in);
    fclose(out);
}

void free_resources(char *buffer) {
    if (buffer) {
        free(buffer);
    }
}
