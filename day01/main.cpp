#include <string>
#include <iostream>
#include <vector>
#include <cstdint>

void read_file(std::vector<std::uint32_t> &buffer) {
    std::string line;
    while (std::getline(std::cin, line)) {
        buffer.push_back(std::stoi(line));
    }
}

int main() {
    std::vector<std::uint32_t> input = {};
    std::vector<std::uint32_t>::iterator main_it;
    std::vector<std::uint32_t>::iterator second_it;
    int target = 2020;

    read_file(input);

    for (main_it = input.begin(); main_it != input.end(); ++main_it) {
        for (second_it = std::next(main_it, 1); second_it != input.end(); ++second_it) {
            if (*main_it + *second_it == target) {
                std::cout << "answer: " << *main_it * *second_it << std::endl;
                return 0;
            }
        }
    }
    return 1;
}
