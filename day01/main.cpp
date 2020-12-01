#include <string>
#include <iostream>
#include <vector>
#include <cstdint>
#include <cassert>

void read_file(std::vector<std::uint32_t> &buffer) {
    std::string line;
    while (std::getline(std::cin, line)) {
        buffer.push_back(std::stoi(line));
    }
}

int first_solution(std::vector<std::uint32_t> &input) {
    int target = 2020;
    std::vector<std::uint32_t>::iterator main_it;
    std::vector<std::uint32_t>::iterator second_it;
    for (main_it = input.begin(); main_it != input.end(); ++main_it) {
        for (second_it = std::next(main_it, 1); second_it != input.end(); ++second_it) {
            if (*main_it + *second_it == target) {
                return *main_it * *second_it;
            }
        }
    }
    return 0;
}

int second_solution(std::vector<std::uint32_t> &input) {
    int target = 2020;
    std::vector<std::uint32_t>::iterator main_it;
    std::vector<std::uint32_t>::iterator second_it;
    std::vector<std::uint32_t>::iterator third_it;
    for (main_it = input.begin(); main_it != input.end(); ++main_it) {
        for (second_it = std::next(main_it, 1); second_it != input.end(); ++second_it) {
            for (third_it = std::next(second_it, 1); third_it != input.end(); ++third_it) {
                if (*main_it + *second_it + *third_it == target) {
                    return *main_it * *second_it * *third_it;
                }
            }
        }
    }
    return 0;
}

int main() {
    std::vector<std::uint32_t> input = {};

    read_file(input);
    std::uint32_t first = first_solution(input);
    std::uint32_t second = second_solution(input);
    assert(first == 988771 && "first solution doesn't match");
    assert(second == 171933104 && "second solution doesn't match");
    std::cout << "first answer: " << first << std::endl;
    std::cout << "second answer: " << second << std::endl;
    return 0;
}
