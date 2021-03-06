#include <vector>
#include <unordered_map>
#include <cassert>
#include <optional>
#include <cstdint>
#include <iostream>

uint64_t find_spoken_number(const std::vector<uint64_t> &input, uint64_t target_turn) {
    std::unordered_map<uint64_t, uint64_t> last_spoken;
    uint64_t first_previous_number;
    std::optional<uint64_t> second_previous_number;
    for (int i = 0; i < input.size(); ++i) {
        last_spoken.emplace(input[i], i + 1);
        first_previous_number = input[i];
    }
    for (int turn = input.size() + 1; turn <= target_turn; ++turn) {
        if (last_spoken.contains(first_previous_number)) {
            first_previous_number = turn - 1 - last_spoken[first_previous_number];
        } else {
            first_previous_number = 0;
        }
        if (second_previous_number) {
            last_spoken[*second_previous_number] = turn - 1;
        }
        second_previous_number = first_previous_number;
    }
    return *second_previous_number;
}
uint64_t first_solution(const std::vector<uint64_t> &input) {
    return find_spoken_number(input, 2020);
}

uint64_t second_solution(const std::vector<uint64_t> &input) {
    return find_spoken_number(input, 30000000);
}

int main() {
    assert(find_spoken_number({0, 3, 6}, 2020) == 436);
    assert(find_spoken_number({1, 3, 2}, 2020) == 1);
    assert(find_spoken_number({3, 1, 2}, 2020) == 1836);

    uint64_t first = first_solution({1, 0, 16, 5, 17, 4});
    uint64_t second = second_solution({1, 0, 16, 5, 17, 4});
    std::cout << "first answer: " << first << std::endl;
    std::cout << "second answer: " << second << std::endl;
    assert(first == 1294 && "first solution doesn't match");
    assert(second == 573522 && "second solution doesn't match");
    return 0;
}
