#include <vector>
#include <iterator>
#include <cstdint>
#include <string>
#include <iostream>
#include <cassert>
#include <complex>
#include <unordered_map>
#include <tuple>

using namespace std::complex_literals;

std::unordered_map<char, std::complex<double>> deltas{
    {'N', 0. + 1i},
    {'S', 0. - 1i},
    {'E', 1. + 0i},
    {'W', -1. + 0i}
};

std::unordered_map<char, int> rotation{
    {'L', 1},
    {'R', -1}
};

std::vector<std::string> read_stdin() {
    std::vector<std::string> input(
            (std::istream_iterator<std::string>(std::cin)),
            std::istream_iterator<std::string>());
    return input;
}

std::tuple<char, double> parse_line(const std::string &line) {
    return std::make_tuple(line[0], std::stol(line.substr(1, line.size())));
}

uint64_t first_solution(const std::vector<std::string> &input) {
    std::complex<double> ship = 0. + 0i;
    std::complex<double> delta = deltas['E'];
    for (auto &line : input) {
        auto [direction, n] = parse_line(line);
        switch (direction) {
            case 'L':
            case 'R':
                delta *= std::pow(1i, (rotation[direction] * (int)n) / 90);
                break;
            case 'F':
                ship += delta * n;
                break;
            default:
                ship += deltas[direction] * n;
        }
    }
    return std::abs(ship.real()) + std::abs(ship.imag());
}

uint64_t second_solution(const std::vector<std::string> &input) {
    std::complex<double> ship = 0. + 0i;
    std::complex<double> waypoint = 10. + 1i;
    for (auto &line : input) {
        auto [direction, n] = parse_line(line);
        switch (direction) {
            case 'L':
            case 'R':
                waypoint *= std::pow(1i, (rotation[direction] * (int)n) / 90);
                break;
            case 'F':
                ship += waypoint * n;
                break;
            default:
                waypoint += deltas[direction] * n;
        }
    }
    return std::abs(ship.real()) + std::abs(ship.imag());
}

int main() {
    const std::vector<std::string> input = read_stdin();
    uint64_t first = first_solution(input);
    uint64_t second = second_solution(input);
    std::cout << "first answer: " << first << std::endl;
    std::cout << "second answer: " << second << std::endl;
    assert(first == 2297 && "first solution doesn't match");
    assert(second == 89984 && "second solution doesn't match");
    return 0;
}
