// file_io.c

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024 // Tamaño del búfer para lectura/escritura

// Abre un archivo para lectura
FILE *open_file_for_reading(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file for reading");
        return NULL;
    }
    return file;
}

// Abre un archivo para escritura
FILE *open_file_for_writing(const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Error opening file for writing");
        return NULL;
    }
    return file;
}

// Lee datos desde un archivo
size_t read_from_file(FILE *file, void *buffer, size_t size) {
    size_t bytes_read = fread(buffer, 1, size, file);
    if (ferror(file)) {
        perror("Error reading from file");
    }
    return bytes_read;
}

// Escribe datos en un archivo
size_t write_to_file(FILE *file, const void *buffer, size_t size) {
    size_t bytes_written = fwrite(buffer, 1, size, file);
    if (ferror(file)) {
        perror("Error writing to file");
    }
    return bytes_written;
}

// Cierra un archivo
int close_file(FILE *file) {
    if (fclose(file) != 0) {
        perror("Error closing file");
        return -1;
    }
    return 0;
}

// Busca una posición específica en el archivo
int seek_in_file(FILE *file, long offset, int whence) {
    if (fseek(file, offset, whence) != 0) {
        perror("Error seeking in file");
        return -1;
    }
    return 0;
}

// Obtiene la posición actual en el archivo
long tell_in_file(FILE *file) {
    long position = ftell(file);
    if (position == -1L) {
        perror("Error telling file position");
    }
    return position;
}

// Verifica si el archivo está al final
int is_end_of_file(FILE *file) {
    return feof(file);
}

// Lee una línea desde el archivo
char *read_line_from_file(FILE *file, char *buffer, size_t size) {
    if (fgets(buffer, size, file) == NULL) {
        if (feof(file)) {
            return NULL; // Fin del archivo
        } else {
            perror("Error reading line from file");
            return NULL;
        }
    }
    return buffer;
}

// Escribe una línea en el archivo
size_t write_line_to_file(FILE *file, const char *line) {
    size_t length = strlen(line);
    size_t bytes_written = fwrite(line, 1, length, file);
    if (ferror(file)) {
        perror("Error writing line to file");
    }
    return bytes_written;
}

// Función auxiliar para leer datos binarios desde un archivo
void *read_binary_data(FILE *file, size_t *size) {
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    void *data = malloc(file_size);
    if (data == NULL) {
        perror("Error allocating memory");
        return NULL;
    }

    if (fread(data, 1, file_size, file) != file_size) {
        perror("Error reading binary data");
        free(data);
        return NULL;
    }
    *size = file_size;
    return data;
}

// Función auxiliar para escribir datos binarios en un archivo
int write_binary_data(FILE *file, const void *data, size_t size) {
    if (fwrite(data, 1, size, file) != size) {
        perror("Error writing binary data");
        return -1;
    }
    return 0;
}
