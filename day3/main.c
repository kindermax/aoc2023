#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "utils.h"

#define MORE_GEARS 1000

bool is_symbol(char sym) {
    return !isdigit(sym) && sym != '.' && sym != '\n';
}

bool is_gear(char sym) {
    return sym == '*';
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

typedef struct {
    int y;
    int x;
} Gear;

int add_gear(int y, int x, Gear *gears, int total) {
    Gear gear = {.y = y, .x = x};
    gears[total++] = gear;
    if (total % MORE_GEARS == 0) {
        gears = realloc(gears, sizeof(Gear) * (total + MORE_GEARS));
    }

    return total;
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

int task2(Input *input) {
    int sum = 0;

    // matrix 140x140 (y*x)
    int numbers[140][140] = {0};
    Gear *gears = malloc(sizeof(Gear) * MORE_GEARS);
    int gears_total = 0;

    for (int y = 0; y < input->lines; y++) {
        char *line = input->data[y];

        int digit_len = 0;
        char digit_chars[5];
        memset(digit_chars, 0, sizeof(digit_chars));

        for (int x = 0; x < strlen(line); x++) {
            char c = line[x];
            if (is_gear(c)) {
                gears_total = add_gear(y, x, gears, gears_total);
            }

            if (isdigit(c)) {
                digit_chars[digit_len] = c;
                digit_len += 1;
            } else if (digit_len > 0) {
                int start = x - digit_len;
                int end = x;
                int num = atoi(digit_chars);

                // set pointer to number for all pos number occupies
                for (int xx = start; xx < end; xx++) {
                    numbers[y][xx] = num;
                }

                memset(digit_chars, 0, sizeof(digit_chars));
                digit_len = 0;
            }
        }
    }

    for (int i = 0; i < gears_total; i++) {
        Gear gear = gears[i];
        int adjacent[8] = {0};
        int adjacent_found = 0;

        // left
        int num = numbers[gear.y][gear.x - 1];
        if (num != 0) {
            adjacent[adjacent_found++] = num;
        }
        // right
        num = numbers[gear.y][gear.x + 1];

        if (num != 0) {
            adjacent[adjacent_found++] = num;
        }

        // top
        for (int x = gear.x - 1; x <= gear.x + 1; x++) {
            num = numbers[gear.y - 1][x];
            if (num != 0 && adjacent[adjacent_found - 1] != num) {
                adjacent[adjacent_found++] = num;
            }
        }

        // bottom
        for (int x = gear.x - 1; x <= gear.x + 1; x++) {
            num = numbers[gear.y + 1][x];
            if (num != 0 && adjacent[adjacent_found - 1] != num) {
                adjacent[adjacent_found++] = num;
            }
        }

        if (adjacent_found == 2) {
            sum += adjacent[0] * adjacent[1];
            adjacent[0] = 0;
            adjacent[1] = 0;
        }
    }

    free(gears);

    return sum;
}

int main() {
    Input input = read_input("input.txt");

    int result1 = task1(&input);
    printf("[task1] %d\n", result1);

    int result2 = task2(&input);
    printf("[task2] %d\n", result2);

    for (int i = 0; i < input.lines; i++) {
        free(input.data[i]);
    }
    free(input.data);
    return 0;
}
