#include <vector>
#include <string>
#include <iostream>
#include <iterator>
#include <utility>
#include <memory>
#include <unordered_map>
#include <regex>
#include <cassert>

std::pair<std::vector<std::string>, std::vector<std::string>> read_stdin() {
    std::vector<std::string> rules;
    std::vector<std::string> messages;
    std::string line;
    while(std::getline(std::cin, line)) {
        if (line.empty()) {
            break;
        }
        rules.push_back(std::move(line));
    }
    while(std::getline(std::cin, line)) {
        messages.push_back(std::move(line));
    }
    return std::make_pair(std::move(rules), std::move(messages));
}

std::string build_rule_string(std::string &&term) {
    std::stringstream input(term), out;
    std::string temp;
    while (!input.eof()) {
        input >> temp;
        out << "(" << temp << ")";
    }
    return out.str();
}

std::regex build_regex(const std::string &key,
    std::unordered_map<std::string, std::string> terminal_rules,
    std::unordered_map<std::string, std::string> unresolved_rules) {

    std::regex pattern(R"(\((\d+)\))");
    while (!unresolved_rules.empty()) {
        auto rule_it = std::begin(unresolved_rules);
        while (rule_it != std::end(unresolved_rules)) {
            auto pattern_it = std::sregex_iterator(rule_it->second.begin(), rule_it->second.end(), pattern);
            auto pattern_end = std::sregex_iterator();
            if (pattern_it == pattern_end) {
                terminal_rules.emplace(rule_it->first, rule_it->second);
                rule_it = unresolved_rules.erase(rule_it);
            } else {
                for (auto i = pattern_it; i != pattern_end; ++i) {
                    std::smatch match = *i;
                    std::string match_str(match[1].str());
                    if (terminal_rules.contains(match_str)) {
                        std::size_t pos = rule_it->second.find(match_str);
                        rule_it->second.replace(pos, match_str.length(), terminal_rules[match_str]);
                        break;
                    }
                }
                ++rule_it;
            }
        }
    }
    //std::cout << terminal_rules[key] << std::endl;
    return std::regex(terminal_rules[key], std::regex::nosubs | std::regex::optimize);
}

int main() {
    auto [rules, messages] = read_stdin();
    std::unordered_map<std::string, std::string> terminal_rules;
    std::unordered_map<std::string, std::string> unresolved_rules;
    std::regex terminal_pattern(R"((\d+): "(\w)\")");
    std::regex or_pattern(R"((\d+): (.*) \| (.*))");
    std::regex rules_pattern(R"((\d+): (.*))");
    std::smatch match;
    for (auto &rule : rules) {
        if (std::regex_match(rule, match, terminal_pattern)) {
            terminal_rules.emplace(match[1], match[2]);
        } else if (std::regex_match(rule, match, or_pattern)) {
            std::string left = build_rule_string(match[2]);
            std::string right = build_rule_string(match[3]);
            unresolved_rules.emplace(match[1], "(" + left + "|" + right + ")");
        } else if (std::regex_match(rule, match, rules_pattern)) {
            unresolved_rules.emplace(match[1], "(" + build_rule_string(match[2]) + ")");
        } else {
            assert(false);
        }
    }
    auto message_pattern = build_regex("0", terminal_rules, unresolved_rules);
    uint64_t match_count = 0;
    for (auto &message : messages) {
        if (std::regex_match(message, match, message_pattern)) {
            ++match_count;
        }
    }
    std::cout << "first answer: " << match_count << std::endl;
    assert(match_count == 162 && "first solution doesn't match");

    // Hack for part 2. Repeat the pattern five times which is enough for
    // matching all needed messages.
    unresolved_rules["8"] = "((42)|((42)(42))|((42)(42)(42))|((42)(42)(42)(42))|((42)(42)(42)(42)(42)))";
	unresolved_rules["11"] = "(((42)(31))|((42)(42)(31)(31))|((42)(42)(42)(31)(31)(31))|((42)(42)(42)(42)(31)(31)(31)(31))|((42)(42)(42)(42)(42)(31)(31)(31)(31)(31)))";
    message_pattern = build_regex("0", terminal_rules, unresolved_rules);
    match_count = 0;
    for (auto &message : messages) {
        if (std::regex_match(message, match, message_pattern)) {
            ++match_count;
        }
    }
    std::cout << "second answer: " << match_count << std::endl;
    assert(match_count == 267 && "second solution doesn't match");

    return 0;
}

