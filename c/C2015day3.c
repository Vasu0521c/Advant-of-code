#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

struct santa {
    int i,
        j;
};

int gift_calculator2(char *input) {

    int result = 1;
    int8_t arr[2000][2000] = {0};
    int i = 500;
    int j = 500;
    arr[i][j] = 1;
    int s = 0;

    struct santa sant = {500, 500};
    struct santa robo = {500, 500};

    while (*input != '\0' && *input != EOF) {

        if (s == 0) {
            i = sant.i;
            j = sant.j;
        } else {
            i = robo.i;
            j = robo.j;
        }
        switch (*input) {

            case '^':
                i--;
                if(arr[i][j] == 0)
                    result++;
                arr[i][j] = 1;
                input++;
                if (s == 0) {
                    s = 1;
                    sant.i = i;
                    sant.j = j;
                } else {
                    s = 0;
                    robo.i = i;
                    robo.j = j;
                }
                continue;

            case '>':
                j++;
                if(arr[i][j] == 0)
                    result++;
                arr[i][j] = 1;
                input++;
                if (s == 0) {
                    s = 1;
                    sant.i = i;
                    sant.j = j;
                } else {
                    s = 0;
                    robo.i = i;
                    robo.j = j;
                }
                continue;

            case '<':
                j--;
                if(arr[i][j] == 0)
                    result++;
                arr[i][j] = 1;
                input++;
                if (s == 0) {
                    s = 1;
                    sant.i = i;
                    sant.j = j;
                } else {
                    s = 0;
                    robo.i = i;
                    robo.j = j;
                }
                continue;

            case 'v':
                i++;
                if(arr[i][j] == 0)
                    result++;
                arr[i][j] = 1;
                input++;
                if(s == 0) {
                    s = 1;
                    sant.i = i;
                    sant.j = j;
                } else {
                    s = 0;
                    robo.i = i;
                    robo.j = j;
                }
                continue;
            default:
                input++;
                continue;
        }
    }
  
    return result;
}
int gift_calculator(char *input) {

    int result = 1;
    int8_t arr[2000][2000] = {0};
    int i = 500;
    int j = 500;
    arr[i][j] = 1;
    while (*input != '\0' && *input != EOF) {

        switch (*input) {

            case '^':
                i--;
                if(arr[i][j] == 0)
                    result++;
                arr[i][j] = 1;
                input++;
                continue;

            case '>':
                j++;
                if(arr[i][j] == 0)
                    result++;
                arr[i][j] = 1;
                input++;
                continue;

            case '<':
                j--;
                if(arr[i][j] == 0)
                    result++;
                arr[i][j] = 1;
                input++;
                continue;

            case 'v':
                i++;
                if(arr[i][j] == 0)
                    result++;
                arr[i][j] = 1;
                input++;
                continue;
            default:
                input++;
                continue;
        }
    }
  
    return result;
}

int main() {

    int size = 0;
    int result1,
        result2;

    FILE *fileptr = fopen("../inputs/2015day3.txt", "r");

    fseek(fileptr, 0L, SEEK_END);
    size = ftell(fileptr);

    char *input = malloc(size + 1);
    fseek(fileptr, 0L, SEEK_SET);

    fread(input, 1, size, fileptr);
    input[size] = '\0';

    result1 = gift_calculator(input);
    result2 = gift_calculator2(input);

    printf("Houses got one present : %d\n", result1);
    printf("Houses got one present : %d\n", result2);
    return 0;
}
