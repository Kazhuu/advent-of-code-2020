#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <regex>
#include <cassert>
#include <deque>
#include <unordered_set>

using contained_by = std::unordered_map<std::string, std::unordered_map<std::string, uint32_t>>;

contained_by parse_stdin() {
    contained_by output;
    std::regex root_pattern(R"((\w+ \w+) bags contain)");
    std::regex contains_pattern(R"(,? (\d+) (\w+ \w+) bags?)");
    std::string line;
    while (std::getline(std::cin, line)) {
        std::smatch root_match;
        assert(std::regex_search(line, root_match, root_pattern));
        auto start = std::sregex_iterator(line.begin(), line.end(), contains_pattern);
        auto end = std::sregex_iterator();
        for (std::sregex_iterator i = start; i != end; ++i) {
            std::smatch match = *i;
            if (output.contains(match[2])) {
                output[match[2]].insert(std::make_pair(root_match[1], std::stoi(match[1])));
            } else {
                std::unordered_map<std::string, uint32_t> bag{{root_match[1], std::stoi(match[1])}};
                output.emplace(match[2], std::move(bag));
            }
        }
    }
    return output;
}

uint32_t first_solution(contained_by &input) {
    std::deque<std::string> q({"shiny gold"});
    std::unordered_set<std::string> seen({"shiny gold"});
    while (!q.empty()) {
        std::string bag_name = q.front();
        for (auto &bag : input[bag_name]) {
            if (seen.insert(bag.first).second) {
                q.push_back(bag.first);
            }
        }
        q.pop_front();
    }
    return seen.size() - 1;
}

int main() {
    contained_by input = parse_stdin();
    uint32_t first = first_solution(input);
    //uint32_t second = second_solution(input);
    //assert(first == 643 && "first solution doesn't match");
    //assert(second == 388 && "second solution doesn't match");
    std::cout << "first answer: " << first << std::endl;
    //std::cout << "second answer: " << second << std::endl;
    return 0;
}
