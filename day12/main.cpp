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

std::pair<int64_t, int64_t> rotate(int64_t x, int64_t y, char direction, int64_t degrees) {
    int64_t count = degrees / 90;
    for (int i = 0; i < count; ++i) {
        std::swap(x, y);
        if (direction == 'R') {
            x = -x;
        } else  {
            y = -y;
        }
    }
    return std::make_pair(x, y);
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
    return std::abs(x) + std::abs(y);
}

uint64_t second_solution(const std::vector<std::string> &input) {
    int64_t way_point_x = 10;
    int64_t way_point_y = -1;
    int64_t ship_x = 0;
    int64_t ship_y = 0;
    for (auto &line : input) {
        auto [direction, value] = parse_line(line);
        switch (direction) {
            case 'N':
                way_point_y -= value;
                break;
            case 'S':
                way_point_y += value;
                break;
            case 'E':
                way_point_x += value;
                break;
            case 'W':
                way_point_x -= value;
                break;
            case 'L':
            case 'R':
                std::tie(way_point_x, way_point_y) = rotate(way_point_x, way_point_y, direction, value);
                break;
            case 'F':
                ship_x += value * way_point_x;
                ship_y += value * way_point_y;
                break;
            default:
                std::cout << "wrong command" << std::endl;
                exit(1);
        }
    }
    return std::abs(ship_x) + std::abs(ship_y);
}

int main() {
    int64_t x, y;
    std::tie(x, y) = rotate(3, 2, 'R', 90);
    assert(x == -2 && y == 3);
    std::tie(x, y) = rotate(3, 2, 'L', 90);
    assert(x == 2 && y == -3);
    std::tie(x, y) = rotate(3, 2, 'L', 360);
    assert(x == 3 && y == 2);

    const std::vector<std::string> input = read_stdin();
    uint64_t first = first_solution(input);
    uint64_t second = second_solution(input);
    std::cout << "first answer: " << first << std::endl;
    std::cout << "second answer: " << second << std::endl;
    assert(first == 2297 && "first solution doesn't match");
    assert(second == 89984 && "second solution doesn't match");
    return 0;
}
