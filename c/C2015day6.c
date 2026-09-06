#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void string_process(char *string, int (*arr)[1000]) {

	int val1,
		val2,
		val3,
		val4;

	if (strncmp(string, "toggle", 6) == 0) {
		sscanf(string, "toggle %d,%d through %d,%d", &val1, &val2, &val3, &val4);

		for (int i = val1; i <= val3; i++) {
			for (int j = val2; j <= val4; j++) {
				if (arr[i][j]) {
					arr[i][j] = 0;
				} else {
					arr[i][j] = 1;
				}
			}
		}

	} else if (strncmp(string, "turn on", 7) == 0) {
		sscanf(string, "turn on %d,%d through %d,%d", &val1, &val2, &val3, &val4);

		for (int i = val1; i <= val3; i++) {
			for (int j = val2; j <= val4; j++) {
				arr[i][j] = 1;
			}
		}

	} else {
		sscanf(string, "turn off %d,%d through %d,%d", &val1, &val2, &val3, &val4);

		for (int i = val1; i <= val3; i++) {
			for (int j = val2; j <= val4; j++) {
				arr[i][j] = 0;
			}
		}
	}
}

void string_process2(char *string, int (*arr)[1000]) {

	int val1,
		val2,
		val3,
		val4;

	if (strncmp(string, "toggle", 6) == 0) {
		sscanf(string, "toggle %d,%d through %d,%d", &val1, &val2, &val3, &val4);

		for (int i = val1; i <= val3; i++) {
			for (int j = val2; j <= val4; j++) {
				arr[i][j] += 2;
			}
		}

	} else if (strncmp(string, "turn on", 7) == 0) {
		sscanf(string, "turn on %d,%d through %d,%d", &val1, &val2, &val3, &val4);

		for (int i = val1; i <= val3; i++) {
			for (int j = val2; j <= val4; j++) {
				arr[i][j]++;
			}
		}

	} else {
		sscanf(string, "turn off %d,%d through %d,%d", &val1, &val2, &val3, &val4);

		for (int i = val1; i <= val3; i++) {
			for (int j = val2; j <= val4; j++) {
				if(arr[i][j])
					arr[i][j]--;
			}
		}
	}
}
int light_lit(char *input) {

	int lights_lit = 0;

	int (*arr)[1000] = calloc(1000, sizeof(*arr));

	char *token = strtok(input, "\n");

	while(token != NULL) {
		string_process(token, arr);
		token = strtok(NULL, "\n");
	}

	for (int i = 0; i < 1000; i++) {
		for (int j = 0; j < 1000; j++) {
			if(arr[i][j])
				lights_lit++;
		}
	}

	return lights_lit;
}

int light_brightness(char *input) {

	int total_brightness = 0;

	int (*arr)[1000] = calloc(1000, sizeof(*arr));

	char *token = strtok(input, "\n");

	while(token != NULL) {
		string_process2(token, arr);
		token = strtok(NULL, "\n");
	}

	for (int i = 0; i < 1000; i++) {
		for (int j = 0; j < 1000; j++) {
			total_brightness += arr[i][j];
		}
	}

	return total_brightness;
}

int main() {

    int size,
        result1,
        result2;

    FILE *fileptr = fopen("../inputs/2015day6.txt", "r");

    fseek(fileptr, 0L, SEEK_END);
    size = ftell(fileptr);

    char *input = malloc(size + 1);
    fseek(fileptr, 0L, SEEK_SET);

    fread(input, 1, size, fileptr);
    input[size] = '\0';

	char *original = malloc(size + 1);
	memcpy(original, input, size);

    /* result1 = light_lit(input); */
	result2 = light_brightness(input);

    /* printf("Part 1 Result : %d\n", result1); */
    printf("Part 2 Result : %d\n", result2);

    return 0;
}
