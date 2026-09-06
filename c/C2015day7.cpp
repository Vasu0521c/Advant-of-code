#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>
#include <cstdint>

typedef std::unordered_map <std::string, std::string> unor_str_map;

const std::size_t notf = std::string::npos;

unor_str_map strings;

std::string string_process(std::string line) {

    if (line == "") {
        return "";
    }

    uint16_t operand_a, operand_b;
    
    return line;
}

std::string recursive_function(std::string input) {

    if(input == "")
        return "";
}

void store_map(std::ifstream &input) {
    
    std::string word, operand, operant;

    while (std::getline(input, word)) {

        size_t length = word.find("->");
        operand = word.substr(0, length);
        operant = word.substr(length + 3);

        strings[operant] = operand;
    }
}

int main() {

    int result1, result2;

    std::ifstream read_stream ("../inputs/2015day7.txt");
    if(read_stream.fail()) {
        std::cerr << "Stream failed, errno : " << errno << std::endl;
        return errno;
    }

    store_map(read_stream);

    result1 = std::stoi(recursive_function("a"));

    std::cout << result1 << std::endl;

    read_stream.close();
    return 0;
}
