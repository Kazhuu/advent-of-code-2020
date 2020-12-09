#include <vector>
#include <string>
#include <iostream>
#include <array>
#include <cassert>

std::vector<std::string> read_stdin() {
    std::vector<std::string> input;
    std::string line;
    while (std::getline(std::cin, line)) {
        input.push_back(line);
    }
    return input;
}

std::pair<std::string, std::string> decode(const std::string &instruction) {
    return make_pair(instruction.substr(0, 3), instruction.substr(4, instruction.size()));

}

bool is_jmp_or_nop(std::string &mnemonic) {
    return mnemonic == "jmp" || mnemonic == "nop";
}

std::string change_mnemonic(std::string &mnemonic, std::string &parameter) {
    if (mnemonic == "jmp") {
        return "nop " + parameter;
    }
    return "jmp " + parameter;
}

std::pair<bool, uint32_t> run_program(const std::vector<std::string> &program) {
    std::vector<bool> visited(program.size(), false);
    bool terminated = false;
    uint32_t program_counter = 0;
    uint32_t accumulator = 0;
    do {
        // Check if program terminated successfully before decoding
        // next instruction.
        if (program_counter == program.size()) {
            terminated = true;
            break;
        }
        auto [instruction, parameter] = decode(program.at(program_counter));
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
    return std::make_pair(terminated, accumulator);
}

uint32_t first_solution(const std::vector<std::string> &input) {
    auto [_, accumulator] = run_program(input);
    return accumulator;
}

uint32_t second_solution(const std::vector<std::string> &input) {
    for (int i = 0; i < input.size(); ++i) {
        auto [mnemonic, parameter] = decode(input[i]);
        if (is_jmp_or_nop(mnemonic)) {
            std::vector<std::string> program = input;
            program[i] = change_mnemonic(mnemonic, parameter);
            auto [terminated, accumulator] = run_program(program);
            if (terminated) {
                return accumulator;
            }
        }
    }
    return 0;
}

int main() {
    const std::vector<std::string> input = read_stdin();
    uint32_t first = first_solution(input);
    uint32_t second = second_solution(input);
    assert(first == 1600 && "first solution doesn't match");
    assert(second == 1543 && "second solution doesn't match");
    std::cout << "first answer: " << first << std::endl;
    std::cout << "second answer: " << second << std::endl;
    return 0;
}
