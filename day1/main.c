#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

FILE* read_input(char* filename) {
    FILE* file = fopen(filename, "r");

    if (!file) {
        printf("Error opening file\n");
        exit(1);
    }

    return file;
}

int extract_digit(char* line) {
    char first = '\0';
    char last = '\0';
    for (int i = 0; i < strlen(line); i++) {
        char c = line[i];
        if (c == '\n') {
            break;
        }
        if (isdigit(c)) {
            if (first == '\0') {
                first = c;
            }
            last = c;
        }
    }
    char digit[50];

    sprintf(digit, "%c%c", first, last);
    return atoi(digit);
}

char *digit_words[] = {
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine"
};

char *digit_words_rev[] = {
    "eno",
    "owt",
    "eerht",
    "ruof",
    "evif",
    "xis",
    "neves",
    "thgie",
    "enin"
};

int find_digit_by_word(char* word, int reverse) {
    for (int i = 0; i < 9; i++) {
        char* digit_word;
        if (reverse) {
            digit_word = digit_words_rev[i];
        } else {
            digit_word = digit_words[i];
        }
        if (strcmp(word, digit_word) == 0) {
            // digit is a index + 1
            return i + 1;
        } else if (strstr(word, digit_word) != NULL) {
            // digit is a index + 1
            return i + 1;
        }
    }
    return -1;
}

int extract_digit_words(char* line) {
    char word[50];

    char first = '\0';
    char last = '\0';

    // find first digit in word
    for (int i = 0; i < strlen(line); i++) {
        char c = line[i];
        if (c == '\n') {
            break;
        }
        int digit = -1;
        if (isdigit(c)) {
            digit = atoi(&c);
        } else {
            strncat(word, &c, 1);
            digit = find_digit_by_word(word, 0);
        }
        if (digit != -1 && first == '\0') {
            first = digit + '0'; // convert to char
            strncpy(word, "", sizeof(word));
            break;
        }
    }

    // find last digit in word
    for (int i = strlen(line) - 1; i >= 0; i--) {
        // if last is not empty, do not search for digits anymore
        // last char
        char c = line[i];
        int digit = -1;
        if (isdigit(c)) {
            digit = atoi(&c);
        } else {
            strncat(word, &c, 1);
            digit = find_digit_by_word(word, 1);
        }
        if (digit != -1 && last == '\0') {
            last = digit + '0'; // convert to char
            strncpy(word, "", sizeof(word));
            break;
        }
    }

    char digit[50];
    sprintf(digit, "%c%c", first, last);
    return atoi(digit);
}

int task1(FILE* input) {
    fseek(input, 0, SEEK_SET);

    char line[100];

    int sum = 0;
    while (fgets(line, sizeof(line), input)) {
        int digit = extract_digit(line);
        sum += digit;
    }


    return sum;
}

int task2(FILE* input) {
    fseek(input, 0, SEEK_SET);

    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    int sum = 0;
    while ((nread = getline(&line, &len, input)) != -1) {
        int digit = extract_digit_words(line);
        sum += digit;
    }

    return sum;

}

int main() {
    FILE* input = read_input("input.txt");

    int sum = task1(input);
    printf("[Task1] Sum %d\n", sum);

    int sum2 = task2(input);
    printf("[Task2] Sum %d\n", sum2);

    fclose(input);
    return 0;
}