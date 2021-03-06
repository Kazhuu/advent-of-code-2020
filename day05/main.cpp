#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <cmath>
#include <cassert>
#include <algorithm>

std::vector<std::string> read_stdin() {
    std::vector<std::string> input(
            (std::istream_iterator<std::string>(std::cin)),
            std::istream_iterator<std::string>());
    return input;
}

uint32_t binary_search(const std::string &line, uint32_t index, uint32_t min, uint32_t max) {
    if (line[index] == 'F' || line[index] == 'L') {
        if (index < line.size()) {
            return binary_search(line, index + 1, min, max - std::ceil((max - min) / 2.0));
        }
        return min;
    } else if (line[index] == 'B' || line[index] == 'R') {
        if (index < line.size()) {
            return binary_search(line, index + 1, min + std::ceil((max - min) / 2.0), max);
        }
        return max;
    }
    return min;
}

uint32_t decode_boarding_pass(const std::string &pass) {
    uint32_t row = binary_search(pass.substr(0, 7), 0, 0, 127);
    uint32_t column = binary_search(pass.substr(7, pass.size()), 0, 0, 7);
    return row * 8 + column;
}

std::vector<uint32_t> seat_ids(const std::vector<std::string> &input) {
    std::vector<uint32_t> ids;
    for (auto &pass : input) {
        ids.emplace_back(decode_boarding_pass(pass));
    }
    return ids;
}

uint32_t first_solution(const std::vector<std::string> &input) {
    std::vector<uint32_t> ids = seat_ids(input);
    return *std::max_element(ids.begin(), ids.end());
}

uint32_t second_solution(const std::vector<std::string> &input) {
    std::vector<uint32_t> ids = seat_ids(input);
    std::sort(ids.begin(), ids.end());
    for (int i = 0; i < ids.size(); ++i) {
        if (ids[i] + 1 != ids[i + 1]) {
            return ids[i] + 1;
        }
    }
    return 0;
}

int main() {
    const std::vector<std::string> input = read_stdin();
    assert(binary_search("FBFBBFF", 0, 0, 127) == 44 && "decode row broken");
    assert(binary_search("RLR", 0, 0, 7) == 5 && "decode column broken");
    uint32_t id = decode_boarding_pass("FBFBBFFRLR");
    assert(id == 357 && "decode boarding pass broken");

    uint32_t first = first_solution(input);
    uint32_t second = second_solution(input);
    std::cout << "first answer: " << first << std::endl;
    std::cout << "second answer: " << second << std::endl;
    assert(first == 816 && "first solution doesn't match");
    assert(second == 539 && "second solution doesn't match");
    return 0;
}
