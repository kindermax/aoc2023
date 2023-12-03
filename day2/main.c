#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* read_input(char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error reading input");
        exit(1);
    }

    return file;
}

#define MAX_RED 12
#define MAX_BLUE 14
#define MAX_GREEN 13

bool ends_with(char* str, char tok) {
    return str[strlen(str)-1] == tok;
}


int task1(FILE* input) {
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    int sum = 0;

    while ((nread = getline(&line, &len, input)) != -1) {
        char buf[len];
        strcpy(buf, line);

        char* token = strtok(buf, " ");
        token = strtok(NULL, " ");
        int game_num = atoi(token);
        bool game_success = false;

        token = strtok(NULL, " ");
        while (token) {
            int cube_amount = atoi(token);
            char *cube_color = strtok(NULL, " ");

            if (ends_with(cube_color, ',')
                || ends_with(cube_color, ';')
                || ends_with(cube_color, '\n')
                ) {
                cube_color[strlen(cube_color)-1] = '\0';
            }

            if (strcmp(cube_color, "red") == 0) {
                game_success = cube_amount <= MAX_RED;
            } else if (strcmp(cube_color, "blue") == 0) {
                game_success = cube_amount <= MAX_BLUE;
            } else if (strcmp(cube_color, "green") == 0) {
                game_success = cube_amount <= MAX_GREEN;
            } else {
                printf("Unknown color %s\n", cube_color);
                exit(1);
            }

            if (!game_success) {
                break;
            }

            token = strtok(NULL, " ");
        }

        if (game_success) {
            printf("Game %d: %s\n", game_num, "possible");
            sum += game_num;
        } else {
            printf("Game %d: %s\n", game_num, "impossible");
        }
    }

    return sum;

}

int main() {
    FILE* input = read_input("../input.txt");

    int result1 = task1(input);
    printf("[task1] %d\n", result1);
    return fclose(input);
}
