#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <list>

std::vector<std::vector<char>> read_stdin() {
    std::vector<std::vector<char>> input;
    std::string line;
    while (std::getline(std::cin, line)) {
        std::vector<char> temp_line;
        for (char &c : line) {
            temp_line.push_back(c);
        }
        input.emplace_back(std::move(temp_line));
    }
    return input;
}

/**
 * Print given map like in the puzzle. Not used in the final solution.
 */
void print_map(const std::vector<std::vector<char>> &map) {
    for (const std::vector<char> &line : map) {
        for (const char &c : line) {
            std::cout << c;
        }
        std::cout << "\n";
    }
}

/**
 * Count trees on the path with given moving coordinates.
 */
int count_trees(const std::vector<std::vector<char>> &map, std::uint32_t move_x, std::uint32_t move_y) {
    std::uint32_t x = 0;
    std::uint32_t y = 0;
    std::uint32_t tree_count = 0;
    do {
        if (map.at(y).at(x) == '#') {
            tree_count++;
        }
        x += move_x;
        y += move_y;
        x = x % map[0].size();
    } while (y < map.size());
    return tree_count;
}

int first_solution(const std::vector<std::vector<char>> &map) {
    std::uint32_t move_x = 3;
    std::uint32_t move_y = 1;
    return count_trees(map, move_x, move_y);
}

int second_solution(const std::vector<std::vector<char>> &map) {
    std::list<std::pair<std::uint32_t, std::uint32_t>> slopes = {{1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2}};
    std::uint32_t result = 1;
    for (auto &slope : slopes) {
        result *= count_trees(map, slope.first, slope.second);
    }
    return result;
}

int main() {
    const std::vector<std::vector<char>> map = read_stdin();
    std::cout << "map size x=" << map[0].size() << ", y=" << map.size() << std::endl;
    std::uint32_t first = first_solution(map);
    std::uint32_t second = second_solution(map);
    assert(first == 178 && "first solution doesn't match");
    assert(second == 3492520200 && "second solution doesn't match");
    std::cout << "first answer: " << first << std::endl;
    std::cout << "second answer: " << second << std::endl;
    return 0;
}
