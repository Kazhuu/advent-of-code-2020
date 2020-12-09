#include <vector>
#include <iostream>
#include <iterator>
#include <deque>
#include <algorithm>
#include <cassert>

std::vector<uint64_t> read_stdin() {
    std::vector<uint64_t> input(
            (std::istream_iterator<uint64_t>(std::cin)),
            std::istream_iterator<uint64_t>());
    return input;
}

bool combinations(std::deque<uint64_t> &input, uint64_t target) {
    std::vector<bool> mask(input.size());
    std::fill(mask.end() - 2, mask.end(), true);
    do {
        uint64_t temp = 0;
        for (int i = 0; i < input.size(); ++i) {
            if (mask[i]) {
                temp += input[i];
            }
        }
        if (temp == target) {
            return true;
        }
    } while (std::next_permutation(mask.begin(), mask.end()));
    return false;
}

uint64_t first_solution(const std::vector<uint64_t> &input) {
    std::deque<uint64_t> window(input.begin(), input.begin() + 25);
    for (int i = 25; i < input.size(); ++i) {
        uint64_t target = input[i];
        if (!combinations(window, target)) {
            return target;
        }
        window.push_back(input[i]);
        window.pop_front();
    }
    return 0;
}

int main() {
    std::vector<uint64_t> input = read_stdin();
    //uint64_t first = first_solution(input);
    uint32_t second = second_solution(input);
    std::cout << "first answer: " << first << std::endl;
    //std::cout << "second answer: " << second << std::endl;
    assert(first == 3199139634 && "first solution doesn't match");
    //assert(second == 539 && "second solution doesn't match");
    return 0;
}
