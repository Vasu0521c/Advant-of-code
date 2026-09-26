#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char *handle_file_operations(void) {

    int size;
    char *input;

    FILE *ptr = fopen("../inputs/2015day20.txt", "rb");

    if (ptr == NULL) {
        printf("File operation failed\n");
        exit(1);
    }

    fseek(ptr, 0L, SEEK_END);
    size = ftell(ptr);

    while (size == -1)
        size = ftell(ptr);

    fseek(ptr, 0L, SEEK_SET);
    input = malloc(size + 1);

    if (input == NULL) {
        printf("Malloc failed\n");
        exit(1);
    }

    fread(input, 1, size, ptr);
    input[size] = '\0';
    fclose(ptr);
    return input;
}

int get_value(char *input) {

    int result = 0;

    while (*(input + 1) != '\0') {
        result = (result * 10) + (*input - '0');
        input++;
    }

    return result;
}

int get_presents2(int house, int times) {
    
    int result, i, root;
    result = i = 0;
    root = (int) sqrt(house);

    while (i < root) {
        ++i;

        if (house % i == 0) {
            if (house / i <= 50) 
                result += i * times;
            if (i <= 50) 
                result += (house / i) * times;
        }
    }

    if (house % i == 0)
        if (house / i <= 50) 
            result += i * times;

    return result;
}

int get_presents(int house, int times) {
    
    int result, i, root;
    result = i = 0;
    root = (int) sqrt(house);

    while (i < root) {
        i++;

        if (house % i == 0) {
            result += (house / i) * times;
            result += i * times;
        }

    }

    if (house % i == 0)
        result += i * times;

    return result;
}

int find_range(int value) {

    int result, i, incr;
    result = i = 0;
    incr   = 100;

    for (i = 100; result < value; i += incr) {
        result = get_presents(i, 10);
    }

    return i;
}

int get_minimum_valueb(int b_v, int value) {

    int i, result;

    result = 0;
    for (i = b_v; result < value; i++) {
        result = get_presents2(i, 11);
    }

    return i - 1;
}

int get_minimum_value(int value) {

    int i, range, result, real;

    range = find_range(value);
    result = 0;

    for (i = 10; i < range; i *= 10)
        real = i;

    range /= real;
    real *= range;

    for (i = real; result < value; i++) {
        result = get_presents(i, 10);
    }

    return i - 1;
}

int main(void) {

    char *input;
    int value, result1, result2;

    input = handle_file_operations();
    value = get_value(input);
    free(input);

    result1 = get_minimum_value(value);
    result2 = get_minimum_valueb(result1, value);
    printf("House number : %d\n", result1);
    printf("House number : %d\n", result2);

    return 0;
}
