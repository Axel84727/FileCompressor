#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include <stddef.h>
#include <stdint.h>
#include <string.h>

void* allocate_memory(size_t size) {
    void* ptr = malloc(size);
    if (ptr == NULL) {
        fprintf(stderr, "Error: No se pudo asignar memoria de tamaño %zu bytes.\n", size);
        return NULL;
    }
    return ptr;
}

void deallocate_memory(void* ptr) {
    if (ptr != NULL) {
        free(ptr);
    }
}

void* reallocate_memory(void* ptr, size_t new_size) {
    void* new_ptr = realloc(ptr, new_size);
    if (new_ptr == NULL) {
        fprintf(stderr, "Error: No se pudo reasignar memoria a tamaño %zu bytes.\n", new_size);
        return NULL;
    }
    return new_ptr;
}

unsigned int gcd(unsigned int a, unsigned int b) {
    while (b != 0) {
        unsigned int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

unsigned int lcm(unsigned int a, unsigned int b) {
    if (a == 0 || b == 0) return 0;
    return (a / gcd(a, b)) * b;
}



// XOR encoding and decoding for simplicity
void encode_data(const unsigned char* input, size_t input_size, unsigned char* output) {
    const unsigned char key = 0xAA; // Example XOR key
    for (size_t i = 0; i < input_size; ++i) {
        output[i] = input[i] ^ key;
    }
}

void decode_data(const unsigned char* input, size_t input_size, unsigned char* output) {
    const unsigned char key = 0xAA; // Same XOR key used for decoding
    for (size_t i = 0; i < input_size; ++i) {
        output[i] = input[i] ^ key;
    }
}

#include <stddef.h>
#include <string.h>
#include <stdlib.h>

// Function to copy a string
char* string_copy(const char* str) {
    if (str == NULL) return NULL;

    size_t length = strlen(str) + 1; // +1 for null terminator
    char* copy = (char*)malloc(length * sizeof(char));
    if (copy == NULL) return NULL; // Memory allocation failed

    memcpy(copy, str, length); // Copy the string
    return copy;
}

// Function to compare two strings
int string_compare(const char* str1, const char* str2) {
    if (str1 == NULL || str2 == NULL) {
        // Handle NULL pointers, if necessary
        return (str1 == str2) ? 0 : (str1 == NULL ? -1 : 1);
    }
    return strcmp(str1, str2); // Use the standard library function to compare
}

#include <stdio.h>
#include <stdlib.h>

// Function to open a file with the specified mode
FILE* open_file(const char* filename, const char* mode) {
    if (filename == NULL || mode == NULL) return NULL; // Handle null pointers
    FILE* file = fopen(filename, mode);
    return file; // Return the file pointer, or NULL if the file could not be opened
}

// Function to close a file
void close_file(FILE* file) {
    if (file != NULL) {
        fclose(file); // Close the file if it is open
    }
}

// Function to read data from a file into a buffer
size_t read_file(FILE* file, unsigned char* buffer, size_t buffer_size) {
    if (file == NULL || buffer == NULL) return 0; // Handle null pointers

    // Read data from the file into the buffer
    size_t bytes_read = fread(buffer, 1, buffer_size, file);
    return bytes_read; // Return the number of bytes read
}

#include <stdio.h>

// Function to print an error message
void print_error(const char* message) {
    if (message != NULL) {
        fprintf(stderr, "Error: %s\n", message); // Print the error message to stderr
    }
}
