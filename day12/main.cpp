#include <vector>
#include <iterator>
#include <cstdint>
#include <string>
#include <iostream>
#include <cassert>
#include <tuple>

std::vector<std::string> read_stdin() {
    std::vector<std::string> input(
            (std::istream_iterator<std::string>(std::cin)),
            std::istream_iterator<std::string>());
    return input;
}

std::tuple<char, int64_t> parse_line(const std::string &line) {
    return std::make_tuple(line[0], std::stol(line.substr(1, line.size())));
}

uint64_t first_solution(const std::vector<std::string> &input) {
    int64_t rotation = 0;
    int64_t x = 0;
    int64_t y = 0;
    for (auto &line : input) {
        auto [direction, value] = parse_line(line);
        switch (direction) {
            case 'N':
                y -= value;
                break;
            case 'S':
                y += value;
                break;
            case 'E':
                x += value;
                break;
            case 'W':
                x -= value;
                break;
            case 'L':
                rotation = (rotation - value) % 360;
                break;
            case 'R':
                rotation = (rotation + value) % 360;
                break;
            case 'F':
                if (rotation == 0) {
                    x += value;
                } else if (rotation == 90 || rotation == -270) {
                    y += value;
                } else if (rotation == 180 || rotation == -180) {
                    x -= value;
                } else if (rotation == 270 || rotation == -90) {
                    y -= value;
                } else {
                    std::cout << "wrong degree" << std::endl;
                    exit(1);
                }
                break;
            default:
                std::cout << "wrong command" << std::endl;
                exit(1);
        }
    }
    return x + y;
}

int main() {
    const std::vector<std::string> input = read_stdin();
    uint64_t first = first_solution(input);
    //uint64_t second = second_solution(map);
    std::cout << "first answer: " << first << std::endl;
    //std::cout << "second answer: " << second << std::endl;
    //assert(first == 2361 && "first solution doesn't match");
    //assert(second == 2119 && "second solution doesn't match");
    return 0;
}
