#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int task1() {
    FILE* file = fopen("input_1.txt", "r");

    if (!file) {
        printf("Error opening file\n");
        exit(1);
    }

    char line[100];

    int sum = 0;
    while (fgets(line, sizeof(line), file)) {
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
        sum += atoi(digit);
    }

    fclose(file);

    return sum;
}

int main() {
    int sum = task1();
    printf("[Task1] Sum %d\n", sum);
    return 0;
}