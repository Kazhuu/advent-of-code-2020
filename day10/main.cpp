#include <deque>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <cassert>

std::deque<uint32_t> read_stdin() {
    std::deque<uint32_t> input(
            (std::istream_iterator<uint32_t>(std::cin)),
            std::istream_iterator<uint32_t>());
    return input;
}

uint32_t first_solution(const std::deque<uint32_t> &input) {
    uint32_t one_diff_count = 0;
    uint32_t three_diff_count = 0;
    for (int i = 0; i < input.size(); ++i) {
        if (input[i + 1] - input[i] == 1) {
            one_diff_count++;
        } else if (input[i + 1] - input[i] == 3) {
            three_diff_count++;
        }
    }
    return one_diff_count * three_diff_count;
}

uint64_t second_solution(const std::deque<uint32_t> &input) {
    uint64_t total_count = 1;
    uint32_t multiplier = 1;
    uint32_t one_count = 0;
    for (int i = 0; i < input.size(); ++i) {
        if (input[i + 1] - input[i] == 1) {
            multiplier += one_count;
            one_count++;
        } else if (input[i + 1] - input[i] == 3) {
            total_count *= multiplier;
            multiplier = 1;
            one_count = 0;
        }
    }
    return total_count;
}

int main() {
    std::deque<uint32_t> input = read_stdin();
    std::sort(input.begin(), input.end());
    input.push_front(0);
    input.push_back(input.back() + 3);

    uint32_t first = first_solution(input);
    uint64_t second = second_solution(input);
    std::cout << "first answer: " << first << std::endl;
    std::cout << "second answer: " << second << std::endl;
    assert(first == 2310 && "first solution doesn't match");
    assert(second == 64793042714624 && "second solution doesn't match");
    return 0;
}
