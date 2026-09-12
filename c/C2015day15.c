#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef int16_t byte;

void display_arr(byte **arr) {

    byte i, j;
    i = 0;
    while (i < 4) {
        j = 0;
        while (j < 5) {
            printf("%d  ", arr[i][j]);
            j++;
        }
        i++;
        printf("\n");
    }
}

int less_much_brute_force(byte **arr, byte limit) {

    int  result = 0;
    int  max    = 0;
    int  cap, dur, fla, tex, cal;
    byte l;

    for (byte i = 0; i < limit; i++) {
        for (byte j = 0; j < limit - i; j++) {
            for (byte k = 0; k < limit - j; k++) {

                l = limit - i - j - k;

                cal = (i * arr[0][4]) +
                      (j * arr[1][4]) +
                      (k * arr[2][4]) +
                      (l * arr[3][4]);

                if (cal != 500)
                    continue;

                cap = (i * arr[0][0]) +
                      (j * arr[1][0]) +
                      (k * arr[2][0]) +
                      (l * arr[3][0]);

                dur = (i * arr[0][1]) +
                      (j * arr[1][1]) +
                      (k * arr[2][1]) +
                      (l * arr[3][1]);

                fla = (i * arr[0][2]) +
                      (j * arr[1][2]) +
                      (k * arr[2][2]) +
                      (l * arr[3][2]);

                tex = (i * arr[0][3]) +
                      (j * arr[1][3]) +
                      (k * arr[2][3]) +
                      (l * arr[3][3]);

                cap = (cap < 0) ? 0 : cap;
                dur = (dur < 0) ? 0 : dur;
                fla = (fla < 0) ? 0 : fla;
                tex = (tex < 0) ? 0 : tex;
                max = cap * dur * fla * tex;
                if (result < max)
                    result = max;
            }
        }
    }
    return result;
}


int too_much_brute_force(byte **arr, byte limit) {

    int  result = 0;
    int  max    = 0;
    int  cap, dur, fla, tex;
    byte l;

    for (byte i = 0; i < limit; i++) {
        for (byte j = 0; j < limit - i; j++) {
            for (byte k = 0; k < limit - j; k++) {

                l   = limit - i - j - k;
                cap = (i * arr[0][0]) +
                      (j * arr[1][0]) +
                      (k * arr[2][0]) +
                      (l * arr[3][0]);

                dur = (i * arr[0][1]) +
                      (j * arr[1][1]) +
                      (k * arr[2][1]) +
                      (l * arr[3][1]);

                fla = (i * arr[0][2]) +
                      (j * arr[1][2]) +
                      (k * arr[2][2]) +
                      (l * arr[3][2]);

                tex = (i * arr[0][3]) +
                      (j * arr[1][3]) +
                      (k * arr[2][3]) +
                      (l * arr[3][3]);

                cap = (cap < 0) ? 0 : cap;
                dur = (dur < 0) ? 0 : dur;
                fla = (fla < 0) ? 0 : fla;
                tex = (tex < 0) ? 0 : tex;
                max = cap * dur * fla * tex;
                if (result < max)
                    result = max;
            }
        }
    }
    return result;
}

void process_input(byte **arr, char *input) {

    _Bool neg_flag;
    byte  i, j;
    i = 0;

    while (*input != '\0') {
        j = 0;
        while (*input != '\n') {

            neg_flag = 0;

            if (*input == '-') {
                neg_flag = 1;
                input++;
            }

            if (*input <= '9' && *input >= '0') {
                arr[i][j] = (byte)(*input - '0');
                if (neg_flag)
                    arr[i][j] *= -1;
                j++;
            }
            input++;
        }
        i++;
        input++;
    }
}

byte **create_array(byte **arr, byte cols, byte rows) {

    arr = malloc(sizeof(byte *) * cols);

    for (int i = 0; i < cols; i++) {
        arr[i] = malloc(sizeof(byte) * rows);
    }

    return arr;
}

int no_of_incredients(char *input) {

    int count = 0;
    while (*input != '\0') {

        if (*input == '\n')
            count++;

        input++;
    }
    return count;
}

int no_of_properties(char *input) {

    int count = 0;
    while (*input != '\n') {

        if (*input <= '9' && *input >= '0')
            count++;

        input++;
    }
    return count;
}

int main() {

    int    size, result1, result2, cap;
    byte   no_of_inc, no_of_pro;
    byte **arr;
    char  *input;

    cap = 100;

    FILE *fileptr = fopen("../inputs/2015day15.txt", "r");
    fseek(fileptr, 0L, SEEK_END);
    size = ftell(fileptr);
    fseek(fileptr, 0L, SEEK_SET);
    input = malloc(size + 1);
    fread(input, 1, size, fileptr);
    input[size] = '\0';

    no_of_inc = no_of_incredients(input);
    no_of_pro = no_of_properties(input);

    arr = create_array(arr, no_of_inc, no_of_pro);

    process_input(arr, input);
    result1 = too_much_brute_force(arr, cap);
    result2 = less_much_brute_force(arr, cap);

    printf("Total score of Cookie : %d\n", result1);
    printf("Total score with 500 calories : %d\n", result2);

    /* display_arr(arr); */

    byte i = 1;

    while (i < no_of_inc) {
        free(arr[i]);
        i++;
    }

    free(arr);
    free(input);
    fclose(fileptr);
    return 0;
}
