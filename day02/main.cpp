#include <string>
#include <vector>
#include <iostream>
#include <cstdint>
#include <tuple>
#include <cassert>

std::vector<std::string> read_stdin() {
    std::vector<std::string> input;
    std::string line;
    while (std::getline(std::cin, line)) {
        input.push_back(line);
    }
    return input;
}

std::tuple<std::string, char, std::uint32_t, std::uint32_t> parse_information(const std::string &line) {
    std::uint32_t start_pos = 0;
    std::uint32_t end_pos = line.find("-");
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

std::uint32_t count_occurences(const std::string &line, char character) {
    std::uint32_t count = 0;
    for (int i = 0; i < line.size(); ++i) {
        if (line[i] == character) {
            count++;
        }
    }
    return count;
}

int first_solution(const std::vector<std::string> &input) {
    std::uint32_t valid_passwords = 0;
    for (const auto &line : input) {
        auto [password, character, min, max] = parse_information(line);
        std::uint32_t count = count_occurences(password, character);
        if (count >= min && count <= max) {
            valid_passwords++;
        }
    }
    return valid_passwords;
}

int second_solution(std::vector<std::string> &input) {
    std::uint32_t valid_passwords = 0;
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
    std::uint32_t first = first_solution(input);
    std::uint32_t second = second_solution(input);
    assert(first == 643 && "first solution doesn't match");
    assert(second == 388 && "second solution doesn't match");
    std::cout << "first answer: " << first << std::endl;
    std::cout << "second answer: " << second << std::endl;
    return 0;
}
