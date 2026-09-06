#include <stdio.h>
#include <stdlib.h>

int string_decider2(char *input) {

    int nice_string,
        naughty_string;

    int pair_twins_count,
        three_letter_palindrome_count;

    nice_string = naughty_string = 0;

    while (*input != '\0') {

        pair_twins_count              = 0;
        three_letter_palindrome_count = 0;

        int pair_twins_array[200][200] = {0};
        int avoid_checking_for_TLPC = 0;

        while (*input != '\n' && *input != '\0') {

            if(*(input + 2) == '\n') {

                avoid_checking_for_TLPC = 1;
            }

            if (((*input == *(input + 1)) && (*(input + 1) == *(input + 3))) ||
                (*input != *(input + 1)) ||
                (*input != *(input + 2))) {

                if (pair_twins_array[*input][*(input + 1)] >= 1) {

                    pair_twins_array[*input][*(input + 1)]++;
                    pair_twins_count++;

                } else {
                    pair_twins_array[*input][*(input + 1)]++;
                }
            }

            if (avoid_checking_for_TLPC == 0 && *input == *(input + 2)) {
                three_letter_palindrome_count++;
            }

            input++;
        }

        if(pair_twins_count >= 1 && three_letter_palindrome_count >= 1) {
            nice_string++;
        }

        else {
            naughty_string++;
        }

        input++;
    }

    return nice_string;
}


int string_decider(char *input) {

    int nice_string,
        naughty_string;

    int three_vowels_counter,
        twice_letter_counter,
        unwanted_string_counter;

    nice_string    = 0;
    naughty_string = 0;

    while (*input != '\0' && *input != EOF) {

        three_vowels_counter    = 0;
        twice_letter_counter    = 0;
        unwanted_string_counter = 0;

        while (*input != '\n') {

            if (*input == *(input+1)) {
                twice_letter_counter = 1;
            }

            if ((*input == 'a') ||
                (*input == 'e') ||
                (*input == 'i') ||
                (*input == 'o') ||
                (*input == 'u')) {

                three_vowels_counter++;
            }

            if ((*input == 'a' && *(input + 1) == 'b') ||
                (*input == 'c' && *(input + 1) == 'd') ||
                (*input == 'p' && *(input + 1) == 'q') ||
                (*input == 'x' && *(input + 1) == 'y')) {

                unwanted_string_counter = 1;
            }

            input++;
        }

        if (twice_letter_counter >= 1 &&
            three_vowels_counter >= 3 &&
            unwanted_string_counter == 0) {

            nice_string++;

        } else
            naughty_string++;

        input++;
    }

    return nice_string;
}

int main() {

    int size,
        result1,
        result2;

    FILE *fileptr = fopen("../inputs/2015day5.txt", "r");

    fseek(fileptr, 0L, SEEK_END);

    size = ftell(fileptr);
    char *input = malloc(size + 1);

    fseek(fileptr, 0L, SEEK_SET);

    fread(input, 1, size, fileptr);

    input[size] = '\0';

    result1 = string_decider(input);
    result2 = string_decider2(input);

    printf("Number of nice strings : %d\n", result1);
    printf("Number of nice strings : %d\n", result2);

    free(input);
    return 0;
}
