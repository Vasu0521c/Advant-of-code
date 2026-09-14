#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PROPS_COUNT 10

typedef int8_t byte;

typedef struct {

    byte *val;
    byte  mode;

} params;

//=============================//

int   get_full_value(char *input);
int match_values(char **string, params *pars, byte index);
char *skip(char *input, char target);

//===========================//

int handle_diffs(char **string, char *str, params *pars, int index, int val) {

    if (index == 1 || index == 7) {
        if (pars -> val[index] < val) {
            str     = str + 3;
            *string = str;
            return 1;
        }
    }

    else if (index == 3 || index == 6) {
        if (pars -> val[index] > val) {
            str     = str + 3;
            *string = str;
            return 1;
        }
    }

    else if (pars -> val[index] == val) {
        str     = str + 3;
        *string = str;
        return 1;
    }
    return 0;
}

int match_values(char **string, params *pars, byte index) {

    int   val;
    char *str = *string;

    str = skip(str, ':');
    val = get_full_value(str);

    if (pars -> mode == 2) {
        if (handle_diffs(string, str, pars, index, val))
            return 1;
    }

    else if (pars -> val[index] == val) {
        str     = str + 3;
        *string = str;
        return 1;
    }
    
    str     = skip(str, '\n');
    *string = str;
    return 0;
}

char *skip(char *input, char target) {

    while (*input != target)
        input++;

    input += 2;
    return input;
}

int get_full_value(char *input) {

    int value = 0;

    while (*input >= '0' && *input <= '9') {
        value = (value * 10) + (*input - '0');
        input++;
    }

    return value;
}

char *handle_prop(char *input, params *pars, int result) {

    int    dummy_val, match_counter;
    char   val[4];
    char **temp;

    *temp         = skip(input, ':');
    match_counter = 0;

    while (match_counter != 3) {

        memcpy(val, *temp, 3);

        if (strcmp(val, "chi") == 0) {
            dummy_val = match_values(temp, pars, 0);
        }

        else if (strcmp(val, "cat") == 0) {
            dummy_val = match_values(temp, pars, 1);
        }

        else if (strcmp(val, "sam") == 0) {
            dummy_val = match_values(temp, pars, 2);
        }

        else if (strcmp(val, "pom") == 0) {
            dummy_val = match_values(temp, pars, 3);
        }

        else if (strcmp(val, "aki") == 0) {
            dummy_val = match_values(temp, pars, 4);
        }

        else if (strcmp(val, "viz") == 0) {
            dummy_val = match_values(temp, pars, 5);
        }

        else if (strcmp(val, "gol") == 0) {
            dummy_val = match_values(temp, pars, 6);
        }

        else if (strcmp(val, "tre") == 0) {
            dummy_val = match_values(temp, pars, 7);
        }

        else if (strcmp(val, "car") == 0) {
            dummy_val = match_values(temp, pars, 8);
        }

        else {
            dummy_val = match_values(temp, pars, 9);
        }

        if (dummy_val)
            match_counter++;

        else
            break;
    }

    input = *temp;

    if (match_counter == 3)
        return NULL;

    return input;
}

int get_values(char *input, params *pars) {

    int result = 1;
    while (result <= 500) {

        input = handle_prop(input, pars, result);

        if (input == NULL) {
            return result;
        }
        result++;
    }
    return result;
}


char *handle_file_operations(void) {

    int   size;
    char *input;

    FILE *fileptr = fopen("../inputs/2015day16.txt", "r");
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

int main(void) {

    char *input;
    int result1, result2;
    params *pars;

    pars = malloc(sizeof(params));
    byte  val_arr[PROPS_COUNT] = {3, 7, 2, 3, 0, 0, 5, 3, 2, 1};

    pars -> mode = 1;
    pars -> val = val_arr;
    input = handle_file_operations();
    result1 = get_values(input, pars);
    pars -> mode = 2;
    result2 = get_values(input, pars);

    printf("The aunt who sent the gift : Aunt %d\n", result1);
    printf("The real aunt who sent the gift : Aunt %d\n", result2);

    free(input);
    return 0;
}
