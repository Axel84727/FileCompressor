// huffman.h

#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Estructura para un nodo del árbol de Huffman
typedef struct HuffmanNode {
    char character;
    unsigned frequency;
    struct HuffmanNode *left, *right;
} HuffmanNode;

// Estructura para el árbol de Huffman
typedef struct HuffmanTree {
    HuffmanNode *root;
} HuffmanTree;

// Estructura para almacenar códigos de Huffman
typedef struct HuffmanCode {
    char character;
    char *code;
} HuffmanCode;

// Funciones para construir el árbol de Huffman
HuffmanTree *build_huffman_tree(const unsigned *frequencies, size_t size);
HuffmanTree *initialize_huffman_tree();
void free_huffman_tree_memory(HuffmanTree *tree);

// Funciones para generar códigos de Huffman
HuffmanCode *generate_huffman_codes(HuffmanTree *tree, int *count);
void free_huffman_codes(HuffmanCode *codes, int count);

// Funciones para la compresión y descompresión
void compress_file(const char *input_filename, const char *output_filename, HuffmanCode *codes, int code_count);
void decompress_file(const char *input_filename, const char *output_filename, HuffmanTree *tree);

// Funciones para guardar y cargar el árbol de Huffman
void save_huffman_tree(FILE *file, HuffmanNode *node);
HuffmanNode *load_huffman_tree(FILE *file);

// Funciones auxiliares
void handle_error(const char *message);
int read_bit(FILE *input, unsigned char *buffer, int *bit_count);
void write_bit(FILE *output, unsigned char *buffer, int *bit_count, int bit);

#endif // HUFFMAN_H
