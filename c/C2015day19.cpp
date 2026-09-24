#include <iostream>
#include <sstream>
#include <cstdio>
#include <unordered_map>
#include <unordered_set>

typedef std::unordered_multimap<std::string, std::string> unor_map;
typedef std::unordered_set<std::string> unor_str;

char *handle_file_operations(void) {

    int   size;
    char *input;

    FILE *fileptr = fopen("../inputs/2015day19.txt", "r");

    if (fileptr == NULL)
        exit(1);

    fseek(fileptr, 0L, SEEK_END);
    size  = ftell(fileptr);
    input = (char *) std::malloc(size + 1);
    fseek(fileptr, 0L, SEEK_SET);
    fread(input, 1, size, fileptr);

    input[size] = '\0';
    fclose(fileptr);
    return input;
}

void get_values(char *input, unor_map &dict) {

    std::stringstream hell(input);
    std::string key, value;

    while (hell >> key) {

        if (key.length() > 4)
            break;

        hell >> value;
        hell >> value;
        dict.insert({key,value});
    }
}

std::string get_actual_input(char *input) {

    char *st_pt;

    while (*input != '\0') {

        if (*input == '=')
            st_pt = input;

        input++;
    }

    while (*st_pt != '\n')
        st_pt++;

    while (*st_pt != '\n')
        st_pt++;

    return st_pt + 2;
}

int operate_on_string(unor_map &dict, std::string &string) {

    int i, len;
    unor_str strings;
    std::string temp_c(string);
    i  = 0;
    len = string.length();

    while(i + 1 < len) {
        std::string temp_a = {string[i], string[i+1]};
        auto it = dict.count(temp_a);

        if (it) {
            for (auto [it, rangeEnd] = dict.equal_range(temp_a);
                 it != rangeEnd; it++) {

                std::string &temp_b = it -> second;
                temp_c.replace(i, 2, temp_b);
                strings.insert(std::move(temp_c));
                temp_c = string;
            }
        }

        i++;
    }

    i = 0;
    temp_c = string;

    while (string[i] != '\0') {
        std::string temp(1, string[i]);
        auto it = dict.count(temp);

        if (it) {

            for (auto [it, rangeEnd] = dict.equal_range(temp);
                 it != rangeEnd; it++) {

                std::string &temp_b = it -> second;
                temp_c.replace(i, 1, temp_b);
                strings.insert(std::move(temp_c));
                temp_c = string;
            }
        }

        i++;
    }
    return strings.size();
}

int main(void) {

    int         size, result1, result2;
    char       *input;
    std::string ac_in;
    unor_map    dict;

    input = handle_file_operations();
    ac_in = get_actual_input(input);
    get_values(input, dict);
    result1 = operate_on_string(dict, ac_in);

    std::cout << result1 << "\n";

    free(input);
    return 0;
}
