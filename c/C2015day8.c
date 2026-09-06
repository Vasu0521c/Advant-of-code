#include <stdio.h>
#include <stdlib.h>

int chars_in_altered(char *input) {

    int chars_in_line,
        total_chars;

    total_chars = 0;

    while (*input != '\0') {

        chars_in_line = 0;

        while (*input != '\n' && *input != '\0') {

            if (*input == '"' || *input == '\\') {
                input++;
                chars_in_line += 2;
            } else {
                input++;
                chars_in_line++;
            }
        }

        if (*input == '\n')
            input++;
        total_chars += chars_in_line + 2;
    }

    return total_chars;
}

int chars_in_memory(char *input) {

    int chars_in_line,
        total_chars;

    total_chars = 0;

    while (*input != '\0') {

        chars_in_line = 0;

        while (*input != '\n' && *input != '\0') {

            if (*input == '"') {
                input++;
            } else if (*input == '\\' && *(input + 1) == '\\') {
                input += 2;
                chars_in_line++;
            } else if (*input == '\\' && *(input + 1) == '"') {
                input += 2;
                chars_in_line++;
            } else if (*input == '\\' && *(input + 1) == 'x') {
                input += 4;
                chars_in_line++;
            } else {
                input++;
                chars_in_line++;
            }
        }

        if (*input == '\n')
            input++;
        total_chars += chars_in_line;
    }

    return total_chars;
}

int main() {

    int size,
        result1,
        result2;

    FILE *file_ptr = fopen("../inputs/2015day8.txt", "r");
    fseek(file_ptr, 0L, SEEK_END);
    size = ftell(file_ptr);

    char *input = malloc(size + 1);

    fseek(file_ptr, 0L, SEEK_SET);
    fread(input, 1, size, file_ptr);

    input[size]     = '\0';

    int totalchars = 0;
    char *hello = input;

    while (*hello != '\0') {
        if (*hello != '\n' && *hello != '\r') {
            totalchars++;
        }
        hello++;
    }

    result1 = chars_in_memory(input);
    result2 = chars_in_altered(input);
    printf("%d\n", totalchars - result1);
    printf("%d\n", result2 - totalchars);

    free(input);
    return 0;
}
