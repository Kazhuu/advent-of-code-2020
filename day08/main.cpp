#include <vector>
#include <string>
#include <iostream>
#include <array>

std::vector<std::string> read_stdin() {
    std::vector<std::string> input;
    std::string line;
    while (std::getline(std::cin, line)) {
        input.push_back(line);
    }
    return input;
}

std::pair<std::string, std::string> decode(const std::string &instruction) {
    return make_pair(instruction.substr(0, 3), instruction.substr(3, instruction.size()));

}

uint32_t first_solution(const std::vector<std::string> &input) {
    std::vector<bool> visited(input.size(), false);
    uint32_t program_counter = 0;
    uint32_t accumulator = 0;
    do {
        auto [instruction, parameter] = decode(input.at(program_counter));
        if (visited.at(program_counter)) {
            break;
        }
        visited.at(program_counter) = true;
        if (instruction == "acc") {
            accumulator += std::stoi(parameter);
            program_counter++;
        } else if (instruction == "jmp") {
            program_counter += std::stoi(parameter);
        } else if (instruction == "nop") {
            program_counter++;
        } else {
            std::cout << "invalid instruction" << std::endl;
            exit(1);
        }
    } while(true);
    return accumulator;
}

int main() {
    const std::vector<std::string> input = read_stdin();
    uint32_t first = first_solution(input);
    //uint32_t second = second_solution(input);
    //assert(first == 643 && "first solution doesn't match");
    //assert(second == 388 && "second solution doesn't match");
    std::cout << "first answer: " << first << std::endl;
    //std::cout << "second answer: " << second << std::endl;
    return 0;
}
