#include <stdio.h>
#include <stdlib.h>

int calculate_floor_p1(char *input, int size) {

    int floor = 0;
    int i     = 0;
    while (i < size) {
        if(input[i] == '\n') {
            i++ ;
            continue;
        }
        if(input[i] == '(')
            floor++;
        else
            floor--;
        i++;
    }
    return floor;
}

int calculate_floor_p2(char *input, int size) {

    int floor = 0;
    int i     = 0;
    while (i < size) {
      if (floor == -1) {
          return i;
      }
        if(input[i] == '\n') {
            i++ ;
            continue;
        }
        if(input[i] == '(')
            floor++;
        else
            floor--;
        i++;
    }
    return floor;
}

int main() {

	FILE *fileptr = fopen("inputs/2015day1.txt", "r");
    fseek(fileptr, 0L, SEEK_END);

    int size = ftell(fileptr);

    fseek(fileptr, 0L, SEEK_SET);
    char *input = malloc(size + 1);

    fread(input,  1, size, fileptr);
    input[size] = '\0';

    int result1 = calculate_floor_p1(input, size);
    int result2 = calculate_floor_p2(input, size);

    fclose(fileptr);
    free(input);

    printf("floor : %d\n", result1);
    printf("1st basement position : %d\n", result2);
	return 0;
}

