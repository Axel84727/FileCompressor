#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

// Macros y Constantes
#define XOR_KEY 0xAA // Clave XOR utilizada para codificación y decodificación

// Funciones de Manejo de Memoria
void* allocate_memory(size_t size); // Asigna memoria dinámica
void deallocate_memory(void* ptr); // Libera memoria dinámica
void* reallocate_memory(void* ptr, size_t new_size); // Reasigna memoria dinámica

// Funciones Matemáticas Auxiliares
unsigned int gcd(unsigned int a, unsigned int b); // Calcula el máximo común divisor
unsigned int lcm(unsigned int a, unsigned int b); // Calcula el mínimo común múltiplo

// Funciones Auxiliares de Codificación/Decodificación
void encode_data(const unsigned char* input, size_t input_size, unsigned char* output); // Codifica datos
void decode_data(const unsigned char* input, size_t input_size, unsigned char* output); // Decodifica datos

// Funciones para Manipulación de Cadenas
char* string_copy(const char* str); // Copia una cadena de caracteres
int string_compare(const char* str1, const char* str2); // Compara dos cadenas de caracteres

// Funciones de Manejo de Archivos
FILE* open_file(const char* filename, const char* mode); // Abre un archivo con el modo especificado
void close_file(FILE* file); // Cierra un archivo
size_t read_file(FILE* file, unsigned char* buffer, size_t buffer_size); // Lee datos de un archivo en un buffer

// Funciones de Manejo de Errores
void print_error(const char* message); // Imprime un mensaje de error

#endif // UTILS_H
