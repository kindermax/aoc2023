#ifndef AOC2023_UTILS_H
#define AOC2023_UTILS_H

#endif //AOC2023_UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MORE_LINES 1024
#define MORE_CHARS 1024

typedef struct {
    char **data;
    size_t lines;
} Input;

Input read_input(char* filename);
