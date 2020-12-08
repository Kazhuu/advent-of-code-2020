#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <regex>
#include <cassert>
#include <deque>
#include <unordered_set>

// Type for getting bag names that contains this bag.
using contained_t = std::unordered_map<std::string, std::unordered_set<std::string>>;
// Type for getting bags that are contained by this bag and their count.
using contains_t = std::unordered_map<std::string, std::unordered_map<std::string, uint32_t>>;

void parse_stdin(contained_t &contained, contains_t &contains) {
    std::regex root_pattern(R"((\w+ \w+) bags contain)");
    std::regex contains_pattern(R"(,? (\d+) (\w+ \w+) bags?)");
    std::string line;
    while (std::getline(std::cin, line)) {
        std::smatch root_match;
        // Regexp root bag and it must succeed.
        assert(std::regex_search(line, root_match, root_pattern));

        contains.emplace(root_match[1], std::unordered_map<std::string, uint32_t>());

        auto start = std::sregex_iterator(line.begin(), line.end(), contains_pattern);
        auto end = std::sregex_iterator();
        // Loop over contained bags.
        for (std::sregex_iterator i = start; i != end; ++i) {
            std::smatch match = *i;

            contains[root_match[1]].emplace(match[2], std::stoi(match[1]));

            if (!contained.emplace(match[2], std::unordered_set<std::string>({root_match[1]})).second) {
                // If insertion didn't took place, meaning that set already
                // exists. Then add another bag that contains this bag to the
                // set.
                contained[match[2]].insert(root_match[1]);
            }
        }
    }
}

uint32_t count_bags(contains_t &contains, std::string bag_name) {
    uint32_t bag_count = 0;
    for (auto& [bag_name, count] : contains[bag_name]) {
        bag_count += count + count * count_bags(contains, bag_name);
    }
    return bag_count;
}

uint32_t first_solution(contained_t &input) {
    std::deque<std::string> q({"shiny gold"});
    std::unordered_set<std::string> seen({"shiny gold"});
    while (!q.empty()) {
        std::string bag_name = q.front();
        for (auto &bag : input[bag_name]) {
            if (seen.insert(bag).second) {
                q.push_back(bag);
            }
        }
        q.pop_front();
    }
    return seen.size() - 1;
}

uint32_t second_solution(contains_t &contains) {
    return count_bags(contains, "shiny gold");
}

int main() {
    contained_t contained;
    contains_t contains;
    parse_stdin(contained, contains);
    auto bags = contains["shiny gold"];
    uint32_t first = first_solution(contained);
    uint32_t second = second_solution(contains);
    assert(first == 259 && "first solution doesn't match");
    assert(second == 45018 && "second solution doesn't match");
    std::cout << "first answer: " << first << std::endl;
    std::cout << "second answer: " << second << std::endl;
    return 0;
}
