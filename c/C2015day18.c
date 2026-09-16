#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARR_SIZE 100

void display(char (*arr)[ARR_SIZE]) {
    int i = 0;
    int j = 0;

    while (i < ARR_SIZE) {
        j = 0;

        while (j < ARR_SIZE) {
            printf("%c", arr[i][j]);
            j++;
        }

        i++;
        printf("\n");
    }
}

char *handle_file_operations(void) {

    int   size;
    char *input;

    FILE *fileptr = fopen("../inputs/2015day18.txt", "r");

    if (fileptr == NULL)
        exit(1);

    fseek(fileptr, 0L, SEEK_END);
    size  = ftell(fileptr);
    input = malloc(size + 1);
    fseek(fileptr, 0L, SEEK_SET);
    fread(input, 1, size, fileptr);

    input[size] = '\0';
    fclose(fileptr);
    return input;
}

void handle_input(char *input, char (*arr)[ARR_SIZE]) {

    int i, j;
    i = 0;

    while (*input != '\0') {
        j = 0;
        while (*input != '\n') {

            if (*input == '#' || *input == '.') {
                arr[i][j] = *input;
                j++;
                input++;

            } else
                input++;

        }
        input++;
        i++;
    }
}

int check_neighbours(char (*arr)[ARR_SIZE], int x_end, int y_end) {

    int i, j, k, l;
    int count;

    i = x_end - 1;
    j = y_end - 1;
    k = x_end + 1;
    l = y_end + 1;

    count = 0;

    if (i >= 0)
        if (arr[i][y_end] == '#')
            count++;

    if (k < ARR_SIZE)
        if (arr[k][y_end] == '#')
            count++;

    if (j >= 0)
        if (arr[x_end][j] == '#')
            count++;

    if (l < ARR_SIZE)
        if (arr[x_end][l] == '#')
            count++;

    if (i >= 0 && j >= 0)
        if (arr[i][j] == '#')
            count++;

    if (i >= 0 && l < ARR_SIZE)
        if (arr[i][l] == '#')
            count++;

    if (k < ARR_SIZE && j >= 0)
        if (arr[k][j] == '#')
            count++;

    if (k < ARR_SIZE && l < ARR_SIZE)
        if (arr[k][l] == '#')
            count++;

    return count;
}


void check_cornor_lights(char (*arr)[ARR_SIZE]) {

    int  light;
    char chr[100][100];

    for (int i = 0; i < ARR_SIZE; i++) {
        for (int j = 0; j < ARR_SIZE; j++) {

            if (i == 0 && j == 0) {
                arr[i][j] = '#';
                chr[i][j] = '#';
                continue;
            }

            else if (i == 0 && j == ARR_SIZE - 1) {
                arr[i][j] = '#';
                chr[i][j] = '#';
                continue;
            }

            else if (i == ARR_SIZE - 1 && j == 0) {
                arr[i][j] = '#';
                chr[i][j] = '#';
                continue;
            }

            else if (i == ARR_SIZE - 1 && j == ARR_SIZE - 1) {
                arr[i][j] = '#';
                chr[i][j] = '#';
                continue;
            }

            light = check_neighbours(arr, i, j);

            if (arr[i][j] == '#') {

                if (light == 2 || light == 3)
                    chr[i][j] = '#';

                else
                    chr[i][j] = '.';
            } else {

                if (light == 3)
                    chr[i][j] = '#';

                else
                    chr[i][j] = '.';
            }
        }
    }
    memcpy(arr, chr, 100 * 100);
}


void check_lights(char (*arr)[ARR_SIZE]) {

    int  light;
    char chr[100][100];

    for (int i = 0; i < ARR_SIZE; i++) {
        for (int j = 0; j < ARR_SIZE; j++) {

            light = check_neighbours(arr, i, j);

            if (arr[i][j] == '#') {

                if (light == 2 || light == 3)
                    chr[i][j] = '#';

                else
                    chr[i][j] = '.';

            } else {

                if (light == 3)
                    chr[i][j] = '#';

                else
                    chr[i][j] = '.';
            }
        }
    }

    memcpy(arr, chr, 100 * 100);
}


int find_lights(char (*arr)[ARR_SIZE]) {

    int count = 0;

    for (int i = 0; i < ARR_SIZE; i++) {
        for (int j = 0; j < ARR_SIZE; j++) {

            if (arr[i][j] == '#')
                count++;

        }
    }

    return count;
}


int lights_on(char (*arr)[ARR_SIZE], int count) {

    int result, times;
    times = 0;

    while (times < count) {
        check_lights(arr);
        times++;
    }

    result = find_lights(arr);
    return result;
}


int lights_always_on(char (*arr)[ARR_SIZE], int count) {

    int result, times;
    times = 0;

    while (times < count) {
        check_cornor_lights(arr);
        times++;
    }

    result = find_lights(arr);
    return result;
}


int main(void) {

    int   result1, result2;
    char *input;
    char  arr[100][100] = {};

    input = handle_file_operations();
    handle_input(input, arr);
    result1 = lights_on(arr, 100);
    handle_input(input, arr);
    result2 = lights_always_on(arr, 100);

    printf("After 100 times total lights on : %d\n", result1);
    printf("After 100 times with cornors on : %d\n", result2);

    free(input);
    return 0;
}
