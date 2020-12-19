#include <cstdint>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include <regex>
#include <cassert>
#include <algorithm>

// Object to represent one rule for one ticket field.
struct RuleSet {
    std::string name;
    uint64_t first_min;
    uint64_t first_max;
    uint64_t second_min;
    uint64_t second_max;
    uint64_t field_index;

    /**
     * Return true if given value valid for this rule set.
     */
    bool is_valid_value(uint64_t value) const {
        return (value >= first_min && value <= first_max)
            || (value >= second_min && value <= second_max);
    }
};
using rules_t = std::vector<RuleSet>;
// Two dimensional vector to hold tickets and their field numbers.
using tickets_t = std::vector<std::vector<uint64_t>>;
// Set to hold all possible field indexes at specific ticket field index. For
// example ticket field 0 will only possible be field/rule at index 1, 2 or 3.
using possible_fields_t = std::vector<std::unordered_set<uint64_t>>;

rules_t rules;
tickets_t tickets;
tickets_t valid_tickets;

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
            rule_match[1],
            std::stoul(rule_match[2]),
            std::stoul(rule_match[3]),
            std::stoul(rule_match[4]),
            std::stoul(rule_match[5])
        };
        rules.emplace_back(std::move(rule_set));
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
        auto check = [&field](const RuleSet &rule_set) {
            return rule_set.is_valid_value(field);
        };
        if (!std::any_of(rules.begin(), rules.end(), std::move(check))) {
            invalid_sum += field;
        }
    }
    return invalid_sum;
}

/**
 * Collect set of possible field indexes for each field in the ticket.
 */
possible_fields_t collect_possible_fields() {
    possible_fields_t possible_fields;
    possible_fields.resize(valid_tickets.front().size());
    // Iterate over indexes of the fields in the ticket.
    for (int i = 0; i < valid_tickets.front().size(); ++i) {
        // Iterate over all possible rules/fields.
        for (int k = 0; k < rules.size(); ++k) {
            auto check = [&i, &k](const std::vector<uint64_t> &ticket) {
                return rules[k].is_valid_value(ticket[i]);
            };
            // Check that this field is valid for all tickets at this index.
            // Then insert it to possible fields set.
            if (std::all_of(valid_tickets.begin(), valid_tickets.end(), std::move(check))) {
                possible_fields[i].insert(k);
            }
        }
    }
    return possible_fields;
}

/**
 * After collecting set of all possible fields for each index of the ticket,
 * then figure out each fields location in the ticket. Conveniently this puzzle
 * has a solution that the possible fields can be unravelled starting from set
 * that has only one possible index and then working your way up from there.
 */
void find_correct_fields(possible_fields_t &possible_fields) {
    auto size_check = [](const std::unordered_set<uint64_t> &set) -> bool {
        return set.size();
    };
    // Continue as long as there exist a set that contain more than 0 elements.
    while (std::any_of(possible_fields.begin(), possible_fields.end(), std::move(size_check))) {
        for (int i = 0; i < possible_fields.size(); ++i) {
            // We have a set that only contain one possible field.
            if (possible_fields[i].size() == 1) {
                uint64_t field_index = *possible_fields[i].begin();
                rules[field_index].field_index = i;
                // Remove assigned index from all other possible fields sets.
                for (auto &fields_set : possible_fields) {
                    fields_set.erase(field_index);
                }
            }
        }
    }
}

uint64_t first_solution() {
    uint64_t invalid_sum = 0;
    for (int i = 1; i < tickets.size(); ++i) {
        uint64_t sum = ticket_valid(tickets[i]);
        // Collect valid tickets for part two.
        if (sum == 0) {
            valid_tickets.push_back(tickets[i]);
        }
        invalid_sum += sum;
    }
    return invalid_sum;
}

uint64_t second_solution() {
    possible_fields_t possible_fields = collect_possible_fields();
    find_correct_fields(possible_fields);
    uint64_t result = 1;
    // First six rules/fields contain needed "departure" fields.
    for (int i = 0; i < 6; ++i) {
        result *= tickets[0][rules[i].field_index];
    }
    return result;
}

int main() {
    read_stdin();
    uint32_t first = first_solution();
    uint64_t second = second_solution();
    std::cout << "first answer: " << first << std::endl;
    std::cout << "second answer: " << second << std::endl;
    assert(first == 23054 && "first solution doesn't match");
    assert(second == 51240700105297 && "second solution doesn't match");
    return 0;
}
