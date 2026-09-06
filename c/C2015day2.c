#include <stdio.h>
#include <stdlib.h>

#define MIN3(a, b, c) (((a) < (b)) ? (((a) < (c)) ? (a) : (c)) : (((b) < (c)) ? (b) : (c)))
#define MAX3(a, b, c) (((a) > (b)) ? (((a) > (c)) ? (a) : (c)) : (((b) > (c)) ? (b) : (c)))


int paper_calculator1(char *input) {

    int j   = 0;
    int res    = 0;
    int temp   = 0;
    int val[3] = {0};
    while (*input != '\n' && *input != '\0') {
        if (*input != 'x') {
            temp = (temp * 10) + *input - '0';
            input++;
        } else {
            val[j] = temp;
            temp = 0;
            input++;
            j++;
        }
    }
    val[2]     = temp;
    int length = val[0] * val[1];
    int width  = val[1] * val[2];
    int height = val[2] * val[0];
    res        = MIN3(length, width, height);
    length    *= 2;
    width     *= 2;
    height    *= 2;

    res += length + width +height;

    return res;
}

int paper_calculator2(char *input) {

    int j      = 0;
    int res    = 0;
    int temp   = 0;
    int val[3] = {0};

    while (*input != '\n' && *input != '\0') {
        if (*input != 'x') {
            temp = (temp * 10) + *input - '0';
            input++;
        } else {
            val[j] = temp;
            temp = 0;
            input++;
            j++;
        }
    }

    val[2]     = temp;
    res        = val[0] * val[1] * val[2];

    int max    = MAX3(val[0], val[1], val[2]);

    for (int i = 0, k = 0; i <= 2; i++) {
      if (max == val[i] && k == 0) {
          k++;
          continue;
      }
      res += val[i] + val[i];
    }

    return res;
}

int papers_needed1(char *input, int size) {

    int res    = 0;
    int i      = 0;
    int temp   = 0;

    res += paper_calculator1(input);
    while (*input != EOF && *input != '\0') {
        if (*input != '\n') {
            input++;
            continue;
        }
        input++;
        res += paper_calculator1(input);
    }
    return res;
}

int papers_needed2(char *input, int size) {

    int res    = 0;
    int i      = 0;
    int temp   = 0;

    res += paper_calculator2(input);
    while (*input != EOF && *input != '\0') {
        if (*input != '\n') {
            input++;
            continue;
        }
        input++;
        res += paper_calculator2(input);
    }
    return res;
}

int main() {

    int size,
        result1,
        result2;

    FILE *fileptr = fopen("../inputs/2015day2.txt", "r");

    fseek(fileptr, 0L, SEEK_END);
    size = ftell(fileptr);

    char *input = malloc(size + 1);
    fseek(fileptr, 0L, SEEK_SET);

    fread(input, 1, size, fileptr);
    input[size] = '\0';

    /* printf("%s", input); */
    result1 = papers_needed1(input, size);
    result2 = papers_needed2(input, size);

    printf("Part 1 Result : %d\n", result1);
    printf("Part 2 Result : %d\n", result2);

	return 0;
}
