#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <cassert>
#include <ranges>

std::vector<std::vector<std::string>> parse_stdin() {
    std::vector<std::vector<std::string>> output;
    std::vector<std::string> input;
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line != "") {
            input.emplace_back(line);
        } else {
            output.emplace_back(std::move(input));
            input = {};
        }
    }
    // Get the last line because that one is not separated by empty line.
    output.emplace_back(std::move(input));
    return output;
}

uint32_t first_solution(const std::vector<std::vector<std::string>> &input) {
    uint32_t total_count = 0;
    std::set<char> answers;
    for (auto &group : input) {
        for (auto &line : group) {
            for (auto &character : line) {
                answers.insert(character);
            }
        }
        total_count += answers.size();
        answers.clear();
    }
    return total_count;
}

uint32_t second_solution(const std::vector<std::vector<std::string>> &input) {
    uint32_t total_count = 0;
    for (auto &group : input) {
        // Iterate over possible questions from a to z.
        for (int i : std::ranges::iota_view(97, 123)) {
            char question = char(i);
            bool all_answered = true;
            for (auto &line : group) {
                if (line.find(question) == std::string::npos) {
                    all_answered = false;
                    break;
                }
            }
            if (all_answered) {
                total_count++;
            }
        }
    }
    return total_count;
}

int main() {
    const std::vector<std::vector<std::string>> input = parse_stdin();
    uint32_t first = first_solution(input);
    uint32_t second = second_solution(input);
    std::cout << "first answer: " << first << std::endl;
    std::cout << "second answer: " << second << std::endl;
    assert(first == 6748 && "first solution doesn't match");
    assert(second == 3445 && "second solution doesn't match");
    return 0;
}
