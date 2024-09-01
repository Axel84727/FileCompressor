// src/huffman.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "huffman.h"

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

// Función para crear un nuevo nodo del árbol de Huffman
HuffmanNode *create_node(char character, unsigned frequency) {
    HuffmanNode *node = (HuffmanNode *)malloc(sizeof(HuffmanNode));
    if (!node) {
        perror("Error al crear nodo");
        exit(EXIT_FAILURE);
    }
    node->character = character;
    node->frequency = frequency;
    node->left = node->right = NULL;
    return node;
}

// Función para liberar la memoria del árbol de Huffman
void free_huffman_tree(HuffmanNode *node) {
    if (node) {
        free_huffman_tree(node->left);
        free_huffman_tree(node->right);
        free(node);
    }
}

// Función para comparar dos nodos del árbol de Huffman
int compare_nodes(const void *a, const void *b) {
    const HuffmanNode *node_a = *(const HuffmanNode **)a;
    const HuffmanNode *node_b = *(const HuffmanNode **)b;
    return (int)(node_a->frequency - node_b->frequency);
}

// Función para construir el árbol de Huffman
HuffmanTree *build_huffman_tree(const unsigned *frequencies, size_t size) {
    HuffmanNode **nodes = (HuffmanNode **)malloc(size * sizeof(HuffmanNode *));
    if (!nodes) {
        perror("Error al crear cola de prioridad");
        exit(EXIT_FAILURE);
    }

    // Crear nodos iniciales para cada carácter
    for (size_t i = 0; i < size; ++i) {
        nodes[i] = create_node((char)i, frequencies[i]);
    }

    // Construir la cola de prioridad
    qsort(nodes, size, sizeof(HuffmanNode *), compare_nodes);

    // Construir el árbol de Huffman
    while (size > 1) {
        HuffmanNode *left = nodes[0];
        HuffmanNode *right = nodes[1];

        // Crear un nuevo nodo con frecuencia sumada
        HuffmanNode *new_node = create_node('\0', left->frequency + right->frequency);
        new_node->left = left;
        new_node->right = right;

        // Reemplazar los dos nodos con el nuevo nodo
        nodes[0] = new_node;
        memmove(&nodes[1], &nodes[2], (size - 2) * sizeof(HuffmanNode *));
        --size;

        // Reordenar la cola de prioridad
        qsort(nodes, size, sizeof(HuffmanNode *), compare_nodes);
    }

    HuffmanTree *tree = (HuffmanTree *)malloc(sizeof(HuffmanTree));
    if (!tree) {
        perror("Error al crear árbol de Huffman");
        exit(EXIT_FAILURE);
    }
    tree->root = nodes[0];

    free(nodes);
    return tree;
}

// Función recursiva para generar códigos de Huffman
void generate_codes_recursive(HuffmanNode *node, char *prefix, int length, HuffmanCode *codes, int *index) {
    if (node->left == NULL && node->right == NULL) {
        // Nodo hoja
        HuffmanCode code;
        code.character = node->character;
        code.code = (char *)malloc(length + 1);
        if (!code.code) {
            perror("Error al crear código de Huffman");
            exit(EXIT_FAILURE);
        }
        strncpy(code.code, prefix, length);
        code.code[length] = '\0';

        codes[*index] = code;
        (*index)++;
        return;
    }

    if (node->left) {
        prefix[length] = '0';
        generate_codes_recursive(node->left, prefix, length + 1, codes, index);
    }

    if (node->right) {
        prefix[length] = '1';
        generate_codes_recursive(node->right, prefix, length + 1, codes, index);
    }
}

// Función para generar códigos de Huffman
HuffmanCode *generate_huffman_codes(HuffmanTree *tree, int *count) {
    HuffmanCode *codes = (HuffmanCode *)malloc(256 * sizeof(HuffmanCode));
    if (!codes) {
        perror("Error al crear tabla de códigos de Huffman");
        exit(EXIT_FAILURE);
    }

    char prefix[256];
    int index = 0;
    generate_codes_recursive(tree->root, prefix, 0, codes, &index);

    *count = index;
    return codes;
}

// Función para escribir un byte en un archivo de salida
void write_bit(FILE *output, unsigned char *buffer, int *bit_count, int bit) {
    if (*bit_count == 8) {
        fwrite(buffer, 1, 1, output);
        *bit_count = 0;
    }
    if (bit) {
        *buffer |= (1 << *bit_count);
    }
    (*bit_count)++;
}

// Función para comprimir un archivo usando códigos de Huffman
void compress_file(const char *input_filename, const char *output_filename, HuffmanCode *codes, int code_count) {
    // Abrir archivos de entrada y salida
    FILE *input = fopen(input_filename, "rb");
    FILE *output = fopen(output_filename, "wb");
    if (!input || !output) {
        perror("Error al abrir archivos");
        exit(EXIT_FAILURE);
    }

    // Crear tabla de códigos
    unsigned char buffer = 0;
    int bit_count = 0;
    fseek(input, 0, SEEK_END);
    long file_size = ftell(input);
    fseek(input, 0, SEEK_SET);
    
    // Leer el archivo y comprimir
    while (file_size--) {
        unsigned char ch = fgetc(input);
        for (int i = 0; i < code_count; ++i) {
            if (codes[i].character == ch) {
                for (size_t j = 0; j < strlen(codes[i].code); ++j) {
                    write_bit(output, &buffer, &bit_count, codes[i].code[j] - '0');
                }
                break;
            }
        }
    }
    
    // Rellenar el buffer restante
    if (bit_count > 0) {
        fwrite(&buffer, 1, 1, output);
    }

    // Cerrar archivos
    fclose(input);
    fclose(output);
}

// Inserta las nuevas funciones aquí
// Función para guardar el árbol de Huffman en un archivo
void save_huffman_tree(FILE *file, HuffmanNode *node) {
    if (node == NULL) {
        fputc(0, file);
        return;
    }
    fputc(1, file);
    fputc(node->character, file);
    fwrite(&node->frequency, sizeof(unsigned), 1, file);
    save_huffman_tree(file, node->left);
    save_huffman_tree(file, node->right);
}

// Función para cargar el árbol de Huffman desde un archivo
HuffmanNode *load_huffman_tree(FILE *file) {
    int node_type = fgetc(file);
    if (node_type == 0) {
        return NULL;
    }
    char character = fgetc(file);
    unsigned frequency;
    fread(&frequency, sizeof(unsigned), 1, file);
    HuffmanNode *node = create_node(character, frequency);
    node->left = load_huffman_tree(file);
    node->right = load_huffman_tree(file);
    return node;
}

// Función para inicializar el árbol de Huffman
HuffmanTree *initialize_huffman_tree() {
    HuffmanTree *tree = (HuffmanTree *)malloc(sizeof(HuffmanTree));
    if (!tree) {
        perror("Error al inicializar árbol de Huffman");
        exit(EXIT_FAILURE);
    }
    tree->root = NULL;
    return tree;
}

// Función para liberar la memoria utilizada por el árbol de Huffman y sus nodos
void free_huffman_tree_memory(HuffmanTree *tree) {
    if (tree) {
        free_huffman_tree(tree->root);
        free(tree);
    }
}

// Función para manejar errores
void handle_error(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

// Función para liberar la memoria de códigos de Huffman
void free_huffman_codes(HuffmanCode *codes, int count) {
    for (int i = 0; i < count; ++i) {
        free(codes[i].code);
    }
    free(codes);
}

// Función para leer un bit de un archivo comprimido
int read_bit(FILE *input, unsigned char *buffer, int *bit_count) {
    if (*bit_count == 0) {
        if (fread(buffer, 1, 1, input) != 1) {
            return -1; // Error al leer
        }
        *bit_count = 8;
    }
    int bit = (*buffer >> (*bit_count - 1)) & 1;
    (*bit_count)--;
    return bit;
}

// Función para descomprimir un archivo usando el árbol de Huffman
void decompress_file(const char *input_filename, const char *output_filename, HuffmanTree *tree) {
    // Abrir archivos de entrada y salida
    FILE *input = fopen(input_filename, "rb");
    FILE *output = fopen(output_filename, "wb");
    if (!input || !output) {
        perror("Error al abrir archivos");
        exit(EXIT_FAILURE);
    }

    // Inicializar variables para la descompresión
    unsigned char buffer = 0;
    int bit_count = 0;
    HuffmanNode *current_node = tree->root;

    // Leer el archivo comprimido y descomprimir
    while (1) {
        int bit = read_bit(input, &buffer, &bit_count);
        if (bit == -1) {
            break; // Fin del archivo comprimido
        }

        if (bit == 0) {
            current_node = current_node->left;
        } else {
            current_node = current_node->right;
        }

        if (current_node->left == NULL && current_node->right == NULL) {
            // Nodo hoja
            fputc(current_node->character, output);
            current_node = tree->root;
        }
    }

    // Cerrar archivos
    fclose(input);
    fclose(output);
}
