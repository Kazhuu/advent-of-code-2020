#include <string>
#include <iostream>
#include <vector>
#include <cstdint>
#include <cassert>
#include <algorithm>

void read_stdin(std::vector<std::uint32_t> &buffer) {
    std::string line;
    while (std::getline(std::cin, line)) {
        buffer.push_back(std::stoi(line));
    }
}

// Adopted from:
// https://stackoverflow.com/questions/9430568/generating-combinations-in-c
int combinations(std::vector<std::uint32_t> &input, int count) {
    std::vector<bool> mask(input.size());
    std::fill(mask.end() - count, mask.end(), true);
    do {
        std::uint32_t temp = 0;
        std::uint32_t result = 1;
        for (int i = 0; i < input.size(); ++i) {
            if (mask[i]) {
                temp += input[i];
                result *= input[i];
            }
        }
        if (temp == 2020) {
            return result;
        }
    } while (std::next_permutation(mask.begin(), mask.end()));
    return 0;
}

int main() {
    std::vector<std::uint32_t> input = {};
    read_stdin(input);
    std::uint32_t first = combinations(input, 2);
    std::uint32_t second = combinations(input, 3);
    assert(first == 988771 && "first solution doesn't match");
    assert(second == 171933104 && "second solution doesn't match");
    std::cout << "first answer: " << first << std::endl;
    std::cout << "second answer: " << second << std::endl;
    return 0;
}
