#include <string>
#include <vector>
#include <iostream>
#include <cstdint>
#include <tuple>
#include <cassert>
#include <algorithm>

std::vector<std::string> read_stdin() {
    std::vector<std::string> input;
    std::string line;
    while (std::getline(std::cin, line)) {
        input.push_back(line);
    }
    return input;
}

std::tuple<std::string, char, uint32_t, uint32_t> parse_information(const std::string &line) {
    uint32_t start_pos = 0;
    uint32_t end_pos = line.find("-");
    std::string min = line.substr(start_pos, end_pos);
    start_pos = end_pos + 1;
    end_pos = line.find(" ", start_pos);
    std::string max = line.substr(start_pos, end_pos - start_pos);
    start_pos = end_pos + 1;
    end_pos = line.find(" ", start_pos);
    std::string character = line.substr(start_pos, end_pos - start_pos);
    start_pos = end_pos + 1;
    end_pos = line.size();
    std::string password = line.substr(start_pos, end_pos - start_pos);
    return std::make_tuple(password, character.at(0), std::stoi(min), std::stoi(max));
}

int first_solution(const std::vector<std::string> &input) {
    uint32_t valid_passwords = 0;
    for (const auto &line : input) {
        auto [password, character, min, max] = parse_information(line);
        uint32_t count = std::count(password.begin(), password.end(), character);
        if (count >= min && count <= max) {
            valid_passwords++;
        }
    }
    return valid_passwords;
}

int second_solution(std::vector<std::string> &input) {
    uint32_t valid_passwords = 0;
    for (const auto &line : input) {
        auto [password, character, first, second] = parse_information(line);
        if (password[first - 1] == character && password[second - 1] != character) {
            valid_passwords++;
        } else if (password[first - 1] != character && password[second - 1] == character) {
            valid_passwords++;
        }
    }
    return valid_passwords;
}

int main() {
    std::vector<std::string> input = read_stdin();
    uint32_t first = first_solution(input);
    uint32_t second = second_solution(input);
    assert(first == 643 && "first solution doesn't match");
    assert(second == 388 && "second solution doesn't match");
    std::cout << "first answer: " << first << std::endl;
    std::cout << "second answer: " << second << std::endl;
    return 0;
}
