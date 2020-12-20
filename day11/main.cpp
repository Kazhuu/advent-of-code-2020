#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <cassert>
#include <functional>

using map_t = std::vector<std::string>;

map_t read_stdin() {
    std::vector<std::string> input(
            (std::istream_iterator<std::string>(std::cin)),
            std::istream_iterator<std::string>());
    return input;
}

uint64_t total_occupied(const map_t &map) {
    uint64_t result = 0;
    char occupied = '#';
    std::for_each(map.begin(), map.end(), [&result, &occupied](const std::string &map_line) {
            result += std::count(map_line.begin(), map_line.end(), occupied);
    });
    return result;
}

uint64_t count_nearby_occupied(map_t &map, int64_t x, int64_t y) {
    uint64_t occupied_count = 0;
    for (int64_t cy = std::max((int64_t)0, y - 1); cy < std::min((int64_t)map.size(), y + 2); ++cy) {
        for (int64_t cx = std::max((int64_t)0, x - 1); cx < std::min((int64_t)map.front().size(), x + 2); ++cx) {
            if (cx == x && cy == y) {
                continue;
            }
            occupied_count += map[cy][cx] == '#';
        }
    }
    return occupied_count;
}

bool is_direction_occupied(map_t &map, int64_t x, int64_t y, int64_t x_step, int64_t y_step) {
    auto continue_iteration = [&map](int64_t x, int64_t y) {
        bool y_direction = y < map.size() && y >= 0;
        bool x_direction = x < map.front().size() && x >= 0;
        return y_direction && x_direction;
    };
    int64_t cx = x + x_step;
    int64_t cy = y + y_step;
    while (continue_iteration(cx, cy)) {
        if (map[cy][cx] == '#') {
            return true;
        } else if (map[cy][cx] == 'L') {
            return false;
        }
        cx += x_step;
        cy += y_step;
    }
    return false;
}

uint64_t count_seen_occupied(map_t &map, int64_t x, int64_t y) {
    uint64_t occupied = 0;
    occupied += is_direction_occupied(map, x, y, 0, -1); // N
    occupied += is_direction_occupied(map, x, y, 0, 1); // S
    occupied += is_direction_occupied(map, x, y, -1, 0); // W
    occupied += is_direction_occupied(map, x, y, 1, 0); // E
    occupied += is_direction_occupied(map, x, y, 1, -1); // NE
    occupied += is_direction_occupied(map, x, y, -1, -1); // NW
    occupied += is_direction_occupied(map, x, y, 1, 1); // SE
    occupied += is_direction_occupied(map, x, y, -1, 1); // SW
    return occupied;
}

map_t reseat(map_t &map, uint64_t max_occupied_count, std::function<uint64_t(map_t&, int64_t, int64_t)> check_occupied) {
    map_t new_map = map;
    for (int y = 0; y < map.size(); ++y) {
        for (int x = 0; x < map.front().size(); ++x) {
            if (map[y][x] == '.') {
                continue;
            }
            if (map[y][x] == 'L' && check_occupied(map, x, y) == 0) {
                new_map[y][x] = '#';
            } else if (map[y][x] == '#' && check_occupied(map, x, y) > max_occupied_count) {
                new_map[y][x] = 'L';
            }
        }
    }
    return new_map;
}

uint64_t first_solution(map_t map) {
    int64_t previous_seated = -1;
    int64_t current_seated = 0;
    while (previous_seated != current_seated) {
        previous_seated = current_seated;
        map = reseat(map, 3, count_nearby_occupied);
        current_seated = total_occupied(map);
    }
    return previous_seated;
}

uint64_t second_solution(map_t map) {
    int64_t previous_seated = -1;
    int64_t current_seated = 0;
    while (previous_seated != current_seated) {
        previous_seated = current_seated;
        map = reseat(map, 4, count_seen_occupied);
        current_seated = total_occupied(map);
    }
    return previous_seated;
}

int main() {
    map_t test_map1{".#L", "###", "###"};
    assert(total_occupied(test_map1) == 7);
    assert(count_nearby_occupied(test_map1, 1, 0) == 3);
    map_t test_map2{
        ".......#.",
        "...#.....",
        ".#.......",
        ".........",
        "..#L....#",
        "....#....",
        ".........",
        "#........",
        "...#....."
    };
    assert(count_seen_occupied(test_map2, 3, 4) == 8);

    const map_t map = read_stdin();
    uint64_t first = first_solution(map);
    std::cout << "first answer: " << first << std::endl;
    uint64_t second = second_solution(map);
    std::cout << "second answer: " << second << std::endl;
    assert(first == 2361 && "first solution doesn't match");
    assert(second == 2119 && "second solution doesn't match");
    return 0;
}
