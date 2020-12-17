#include <cstdint>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <regex>
#include <cassert>
#include <algorithm>

struct RuleSet {
    uint64_t first_min;
    uint64_t first_max;
    uint64_t second_min;
    uint64_t second_max;
};
using rules_t = std::unordered_map<std::string, RuleSet>;

std::vector<std::vector<uint64_t>> tickets;
rules_t rules;

void read_stdin() {
    std::regex rule_pattern(R"((.+): (\d+)-(\d+) or (\d+)-(\d+))");
    std::regex ticket_patterh(R"((\d+),?)");
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line == "") {
            break;
        }
        std::smatch rule_match;
        std::regex_search(line, rule_match, rule_pattern);
        RuleSet rule_set {
            std::stoul(rule_match[2]),
            std::stoul(rule_match[3]),
            std::stoul(rule_match[4]),
            std::stoul(rule_match[5])
        };
        rules.emplace(rule_match[1], std::move(rule_set));
    }
    while (std::getline(std::cin, line)) {
        std::vector<uint64_t> fields;
        auto start = std::sregex_iterator(line.begin(), line.end(), ticket_patterh);
        auto end = std::sregex_iterator();
        for (std::sregex_iterator i = start; i != end; ++i) {
            std::smatch match = *i;
            fields.emplace_back(std::stoul(match.str()));
        }
        if (fields.size() > 0) {
            tickets.emplace_back(std::move(fields));
        }
    }
}

uint64_t ticket_valid(std::vector<uint64_t> &ticket) {
    uint64_t invalid_sum = 0;
    for (auto &field : ticket) {
        auto check = [&field](std::pair<std::string, RuleSet> rule_set) {
            bool result = (field >= rule_set.second.first_min && field <= rule_set.second.first_max)
                || (field >= rule_set.second.second_min && field <= rule_set.second.second_max);
            return result;
        };
        if (!std::any_of(rules.begin(), rules.end(), check)) {
            invalid_sum += field;
        }
    }
    return invalid_sum;
}

uint64_t first_solution() {
    uint64_t invalid_sum = 0;
    for (int i = 1; i < tickets.size(); ++i) {
        invalid_sum += ticket_valid(tickets[i]);
    }
    return invalid_sum;
}

int main() {
    read_stdin();
    uint32_t first = first_solution();
    //uint64_t second = second_solution(bus_ids);
    std::cout << "first answer: " << first << std::endl;
    //std::cout << "second answer: " << second << std::endl;
    //assert(first == 3966 && "first solution doesn't match");
    //assert(second == 800177252346225 && "second solution doesn't match");
    return 0;
}
