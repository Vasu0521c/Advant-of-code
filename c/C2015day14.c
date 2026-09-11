#include <stdio.h>
#include <stdlib.h>

typedef struct arr_set arr_set;

struct arr_set {

    int *speed_arr;
    int *time_arr;
    int *rest_arr;
};

int get_max(int *arr, int n) {

    int value = 0;
    int i     = 0;
    while (i < n) {

        if (value < arr[i])
            value = arr[i];

        i++;
    }
    return value;
}

int get_full_value(char **actual) {

    char *input = *actual;
    int   value = 0;

    while (*input >= '0' && *input <= '9') {
        value = value * 10 + (*input - '0');
        input++;
    }

    *actual = input;
    return value;
}

int get_total_deers(FILE *ptr) {

    int  count = 0;
    char buff[100];

    while (fgets(buff, sizeof(buff), ptr) != NULL)
        count++;

    return count;
}

int get_value(arr_set arrs, int index, int time) {

    int value     = 0;
    int temp_time = time % (arrs.time_arr[index] + arrs.rest_arr[index]);

    if (temp_time > 0 && temp_time <= arrs.time_arr[index]) {
        value = arrs.speed_arr[index];
    }

    return value;
}

int full_brute_force(arr_set arrs, int time, int n_deers) {

    int result, max, dis_cover, remain, end_time;
    int indi_value[n_deers], indi_points[n_deers];
    int i = 0;

    end_time = time;
    time     = 1;

    while (i < n_deers) {
        indi_value[i]  = 0;
        indi_points[i] = 0;
        i++;
    }

    while (time < end_time) {
        i = 0;

        while (i < n_deers) {
            indi_value[i] += get_value(arrs, i, time);
            i++;
        }

        i   = 0;
        max = get_max(indi_value, n_deers);

        while (i < n_deers) {

            if (max == indi_value[i])
                indi_points[i]++;
            i++;
        }
        time++;
    }

    i = max = 0;
    while (i < n_deers) {

        if (max < (indi_value[i] + indi_points[i])) {
            max    = indi_value[i] + indi_points[i];
            result = indi_points[i];
        }

        i++;
    }

    return result;
}

int get_max_distance_covered(arr_set arrs, int time, int n_deers) {

    int max, indi_value, dis_cover, remain;
    int i = 0;
    max   = 0;

    while (i < n_deers) {

        indi_value  = arrs.speed_arr[i] * arrs.time_arr[i];
        dis_cover   = arrs.time_arr[i] + arrs.rest_arr[i];
        remain      = time / dis_cover;
        indi_value *= remain;
        remain      = time % dis_cover;

        if (remain <= arrs.time_arr[i]) {
            indi_value += arrs.speed_arr[i] * remain;
        }

        else if (remain > arrs.time_arr[i])
            indi_value += arrs.speed_arr[i] * arrs.time_arr[i];

        if (max < indi_value) {
            max = indi_value;
        }

        i++;
    }

    return max;
}

void process_input(char *input, int n_deers, arr_set arrs) {

    int i, j, result;
    int val[3] = {0};
    i          = 0;

    while (*input != '\0') {
        j = 0;
        while (*input != '\n') {

            if (*input >= '0' && *input <= '9') {
                val[j]            = get_full_value(&input);
                arrs.speed_arr[i] = val[0];
                arrs.time_arr[i]  = val[1];
                arrs.rest_arr[i]  = val[2];
                j++;
            }

            input++;
        }
        input++;
        i++;
    }
}

int main(void) {

    arr_set arrs;
    int     size, time, n_deers, result1, result2;

    char   *input;

    FILE   *ptr = fopen("../inputs/2015day14.txt", "r");
    n_deers     = get_total_deers(ptr);

    fseek(ptr, 0L, SEEK_END);
    size = ftell(ptr);
    fseek(ptr, 0L, SEEK_SET);
    input = malloc(size + 1);
    fread(input, 1, size, ptr);
    input[size] = '\0';

    arrs.speed_arr = malloc(sizeof(int) * n_deers);
    arrs.time_arr  = malloc(sizeof(int) * n_deers);
    arrs.rest_arr  = malloc(sizeof(int) * n_deers);
    time           = 2503;
    process_input(input, n_deers, arrs);

    result1 = get_max_distance_covered(arrs, time, n_deers);
    result2 = full_brute_force(arrs, time, n_deers);
    printf("The maximum covered Distance : %d\n", result1);
    printf("The maximum covered Distance with second additions : %d\n",
           result2);
    free(input);
    free(arrs.speed_arr);
    free(arrs.time_arr);
    free(arrs.rest_arr);
    return 0;
}
