#include <stdio.h>
#include <stdlib.h>

void desc_sort(int *arr, int size) {

    int dummy, temp;

    for (int i = 0; i < size; i++) {
        dummy = i;
        for (int j = i; j < size; j++) {

            if (arr[dummy] <= arr[j])
                dummy = j;
        }
        temp       = arr[i];
        arr[i]     = arr[dummy];
        arr[dummy] = temp;
    }
}

void get_values(char *input, int *arr) {

    int value, i;
    value = i = 0;
    while (*input != '\0') {

        while (*input >= '0' && *input <= '9') {
            value = (value * 10) + (*input - '0');
            input++;
        }

        if (value == 0) {
            input++;
            continue;
        }

        arr[i] = value;
        value  = 0;
        i++;
    }
}

int get_elements_count(char *input) {

    int count = 0;

    while (*input != '\0') {

        if (*input == '\n')
            count++;

        input++;
    }
    return count;
}

char *handle_file_operations(void) {

    int   size;
    char *input;

    FILE *fileptr = fopen("../inputs/2015day17.txt", "r");

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

int get_minimum_number_of_combinations(int *arr, int total, int size, int dummy, int *min, int *end, int *x) {

    int value, i;
    value = i = 0;

    if (total < 0)
        return value;

    if (total == 0 && dummy == *end) {
        (*x)++;
    }

    if (total == 0) {
        if (*min > dummy)
            *min = dummy;
        return 1;
    }

    if(size != 0)
        value += get_minimum_number_of_combinations(arr + 1, total, size - 1, dummy, min, end, x);

    if (size != 0)
        value += get_minimum_number_of_combinations(arr + 1, total - arr[i], size - 1, ++dummy, min, end ,x);
     
    return value;
}

int main(void) {

    char *input;
    int  *arr;
    int   size, result1, result2;
    int   total, min, end, x;

    min  = 1000;
    total = 150;
    input = handle_file_operations();
    size  = get_elements_count(input);
    arr   = (int *)malloc(size * sizeof(int));
    end = x = 0;

    get_values(input, arr);
    desc_sort(arr, size);

    result1 = get_minimum_number_of_combinations(arr, total, size, 0, &min, &end, &x);
    end = min;
    result2 = get_minimum_number_of_combinations(arr, total, size, 0, &min, &end, &x);
    result2 = x;

    printf("The number of ways to get sum : %d\n", result1);
    printf("The minimum : %d\n", result2);
    return 0;
}
