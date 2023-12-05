#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MORE_LINES 1024
#define MORE_CHARS 1024


typedef struct {
    char **data;
    size_t lines;
} Input;

Input read_input(char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error reading input");
        exit(1);
    }

    char **lines;
    lines = malloc(sizeof(char *) * MORE_LINES);
    size_t total_lines = 0;
    size_t total_chars = 0;
    char c;

    do {
        c = fgetc(file);
        if (ferror(file)) {
            perror("error reading file");
            exit(1);
        }

        if (feof(file)) {
            if (total_chars != 0) {
                lines[total_lines] = realloc(lines[total_lines], total_chars + 1);
                lines[total_lines][total_chars] = '\0';
                total_lines++;
            }
            break;
        }

        if (total_chars == 0) {
            lines[total_lines] = malloc(MORE_CHARS);
        }

        lines[total_lines][total_chars] = c;
        total_chars++;

        if (c == '\n') {
            lines[total_lines] = realloc(lines[total_lines], total_chars);
            lines[total_lines][total_chars] = '\0';
            total_lines++;
            total_chars = 0;

            if (total_lines % MORE_LINES == 0) {
                size_t new_size = total_lines + MORE_LINES;
                lines = realloc(lines, sizeof (char *) * new_size);
            }
        } else if (total_chars % MORE_CHARS == 0) {
            size_t new_size = total_chars + MORE_CHARS;
            lines[total_lines] = realloc(lines[total_lines], new_size);
        }
    } while (true);

    lines = realloc(lines, sizeof (char *) * total_lines);

    fclose(file);

    Input input = {
        .data = lines,
        .lines = total_lines,
    };
    return input;
}

bool is_symbol(char sym) {
//    return sym == '*';
    return !isdigit(sym) && sym != '.' && sym != '\n';
}

bool find_adjacent_symbol(int digit_len, int pos, char* prev_line, char *line, char *next_line) {
    bool is_left_edge = pos == 0;
    bool is_right_edge = pos + digit_len + 1 >= strlen(line);
    bool is_top_edge = prev_line == NULL;
    bool is_bottom_edge = next_line == NULL;

    // check left
    if (!is_left_edge) {
        if (is_symbol(line[pos - 1])) {
            return true;
        }
    }

    // check right
    if (!is_right_edge) {
        if (is_symbol(line[pos + digit_len])) {
            return true;
        }
    }

    int check_len = digit_len + 2;
    if (is_left_edge) check_len--;
    if (is_right_edge) check_len--;

    int start = is_left_edge ? pos : pos - 1;

    // check top
    if (!is_top_edge) {
        for (int i = start; i < start + check_len; i++) {
            char c = prev_line[i];
            if (is_symbol(c)) {
                return true;
            }
        }
    }

    // check bottom
    if (!is_bottom_edge) {
        for (int i = start; i < start + check_len; i++) {
            char c = next_line[i];
            if (is_symbol(c)) {
                return true;
            }
        }
    }

    return false;
}

int task1(Input *input) {

    int sum = 0;

    for (int l = 0; l < input->lines; l++) {
        char *line = input->data[l];
        char *prev_line = NULL;
        char *next_line = NULL;

        if (l > 0) {
            prev_line = input->data[l-1];
        }
        if (l + 1 <= input->lines) {
            next_line = input->data[l+1];
        }

        int digit_len = 0;
        char digit_chars[5];
        memset(digit_chars, 0, sizeof(digit_chars));

        for (int i = 0; i < strlen(line); i++) {
            char c = line[i];
            if (isdigit(c)) {
                digit_chars[digit_len] = c;
                digit_len += 1;
            } else if (digit_len > 0) {
                int digit = atoi(digit_chars);
                int pos = i - digit_len;
                bool adjacent = find_adjacent_symbol(digit_len, pos, prev_line, line, next_line);
                if (adjacent) {
                    sum += digit;
                }

                memset(digit_chars, 0, sizeof(digit_chars));
                digit_len = 0;
            }
        }
    }

    return sum;
}

int main() {
    Input input = read_input("input.txt");

    int result1 = task1(&input);
    printf("[task1] %d\n", result1);

    // int result2 = task2(input);
    // printf("[task2] %d\n", result2);

    for (int i = 0; i < input.lines; i++) {
        free(input.data[i]);
    }
    free(input.data);
    return 0;
}
