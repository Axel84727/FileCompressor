#ifndef FILE_IO_H
#define FILE_IO_H

#include <stdio.h>
#include <stddef.h>

#define BUFFER_SIZE 1024 // Tamaño del búfer para lectura/escritura

// Abre un archivo para lectura
FILE *open_file_for_reading(const char *filename);

// Abre un archivo para escritura
FILE *open_file_for_writing(const char *filename);

// Lee datos desde un archivo
size_t read_from_file(FILE *file, void *buffer, size_t size);

// Escribe datos en un archivo
size_t write_to_file(FILE *file, const void *buffer, size_t size);

// Cierra un archivo
int close_file(FILE *file);

// Busca una posición específica en el archivo
int seek_in_file(FILE *file, long offset, int whence);

// Obtiene la posición actual en el archivo
long tell_in_file(FILE *file);

// Verifica si el archivo está al final
int is_end_of_file(FILE *file);

// Lee una línea desde el archivo
char *read_line_from_file(FILE *file, char *buffer, size_t size);

// Escribe una línea en el archivo
size_t write_line_to_file(FILE *file, const char *line);

// Función auxiliar para leer datos binarios desde un archivo
void *read_binary_data(FILE *file, size_t *size);

// Función auxiliar para escribir datos binarios en un archivo
int write_binary_data(FILE *file, const void *data, size_t size);

#endif // FILE_IO_H
