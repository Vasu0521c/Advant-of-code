#include <iostream>

int main(int argc, char *argv[]) {

    int password = 0;
    int inputs_n = argc - 1;
    int temp_input_value = 0;
    int temp_locker_pos  = 50;
    int i = 0;
    argv++;

    while (inputs_n--) {

        int j = 0;
        if (argv[i][0] == 'R') {
            argv[i][0] = '+';
            temp_input_value = std::atoi((char *)argv[i]);
            if (temp_input_value >= 100) {
                password += temp_input_value / 100;
            }
            temp_input_value %= 100;
            temp_input_value = 100 - temp_input_value;
            temp_input_value *= -1;
        } else {
            argv[i][0] = '+';
            temp_input_value = std::atoi((char *)argv[i]);
            if (temp_input_value >= 100) {
                password += temp_input_value / 100;
            }
            temp_input_value %= 100;
            temp_input_value = 100 - temp_input_value;
        }
        temp_locker_pos = temp_locker_pos + (temp_input_value);
        if (temp_locker_pos >= 100 || temp_locker_pos <= 0) {
            password += temp_locker_pos / 100;
        }
        temp_locker_pos %= 100;
        if (temp_locker_pos == 0) {
            password++;
            temp_locker_pos = 100;
        }
        argv++;
    }
    std::cout << password << std::endl;
    return 0;
}
