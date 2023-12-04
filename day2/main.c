#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RED 12
#define MAX_BLUE 14
#define MAX_GREEN 13

FILE* read_input(char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error reading input");
        exit(1);
    }

    return file;
}

bool ends_with(char* str, char tok) {
    return str[strlen(str)-1] == tok;
}

int parse_game_num(char* token) {
    token = strtok(NULL, " ");
    return atoi(token);
}

struct GameIteration {
    int amount;
    char *color;
};

typedef struct GameIteration GameIteration;

GameIteration parse_game_iteration(char* token) {
    int amount = atoi(token);
    char *color = strtok(NULL, " ");

    if (ends_with(color, ',')
        || ends_with(color, ';')
        || ends_with(color, '\n')
        ) {
        color[strlen(color)-1] = '\0';
    }

    GameIteration game = {
        .color = color,
        .amount = amount
    };
    return game;
}

int task1(FILE* input) {
    char *line = NULL;
    size_t len = 0;

    int sum = 0;

    while (getline(&line, &len, input) != -1) {
        char* token = strtok(line, " ");
        int game_num = parse_game_num(token);
        bool game_success = false;

        token = strtok(NULL, " ");

        while (token) {
            GameIteration game = parse_game_iteration(token);

            if (strcmp(game.color, "red") == 0) {
                game_success = game.amount <= MAX_RED;
            } else if (strcmp(game.color, "blue") == 0) {
                game_success = game.amount <= MAX_BLUE;
            } else if (strcmp(game.color, "green") == 0) {
                game_success = game.amount <= MAX_GREEN;
            } else {
                printf("Unknown color %s\n", game.color);
                exit(1);
            }

            if (!game_success) {
                break;
            }

            token = strtok(NULL, " ");
        }

        if (game_success) {
            sum += game_num;
        }
    }

    return sum;
}

int task2(FILE* input) {
    char *line = NULL;
    size_t len = 0;

    int sum = 0;

    while (getline(&line, &len, input) != -1) {
        char *token = strchr(line, ':')+1;
        token = strtok(token, " ");

        int max_red = 0;
        int max_blue = 0;
        int max_green = 0;

        while (token) {
            GameIteration game = parse_game_iteration(token);

            if (strcmp(game.color, "red") == 0) {
                max_red = (int)fmax(max_red*1.0, game.amount*1.0);
            } else if (strcmp(game.color, "blue") == 0) {
                max_blue = (int)fmax(max_blue*1.0, game.amount*1.0);
            } else if (strcmp(game.color, "green") == 0) {
                max_green = (int)fmax(max_green, game.amount);
            } else {
                printf("Unknown color %s\n", game.color);
                exit(1);
            }

            token = strtok(NULL, " ");
        }

        sum += max_red * max_blue * max_green;
    }

    return sum;
}

int main() {
    FILE* input = read_input("input.txt");

    int result1 = task1(input);
    printf("[task1] %d\n", result1);

    fseek(input, 0, SEEK_SET);

    int result2 = task2(input);
    printf("[task2] %d\n", result2);

    return fclose(input);
}
