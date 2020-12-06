#include <string>
#include <vector>
#include <iostream>
#include <unordered_set>
#include <cassert>
#include <algorithm>

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
    std::unordered_set<char> answers;
    for (auto &group : input) {
        for (auto &line : group) {
            answers.insert(line.begin(), line.end());
        }
        total_count += answers.size();
        answers.clear();
    }
    return total_count;
}

uint32_t second_solution(const std::vector<std::vector<std::string>> &input) {
    uint32_t total_count = 0;
    std::string seen;
    for (auto &group : input) {
        seen  = group[0];
        for (int i = 1; i < group.size(); ++i) {
            seen.erase(
                std::remove_if(seen.begin(), seen.end(),
                    [&group, &i](char c) { return group[i].find(c) == std::string::npos; }
                ),
                seen.end()
            );
        }
        total_count += seen.size();
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
