#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <cassert>

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

uint64_t count_nearby_occupied(map_t &map, uint64_t x, uint64_t y) {
    uint64_t occupied_count = 0;
    int test = std::max((int64_t)0, (int64_t)y - 1);
    for (uint64_t cy = std::max((int64_t)0, (int64_t)y - 1); cy < std::min(map.size(), y + 2); ++cy) {
        for (uint64_t cx = std::max((int64_t)0, (int64_t)x - 1); cx < std::min(map.front().size(), x + 2); ++cx) {
            if (cx == x && cy == y) {
                continue;
            }
            occupied_count += map[cy][cx] == '#';
        }
    }
    return occupied_count;
}

map_t reseat(map_t &map) {
    map_t new_map = map;
    for (int y = 0; y < map.size(); ++y) {
        for (int x = 0; x < map.front().size(); ++x) {
            if (map[y][x] == '.') {
                continue;
            }
            if (map[y][x] == 'L' && count_nearby_occupied(map, x, y) == 0) {
                new_map[y][x] = '#';
            } else if (map[y][x] == '#' && count_nearby_occupied(map, x, y) > 3) {
                new_map[y][x] = 'L';
            }
        }
    }
    return new_map;
}

uint64_t first_solution(map_t map) {
    uint64_t previous_seated = -1;
    uint64_t current_seated = 0;
    while (previous_seated != current_seated) {
        previous_seated = current_seated;
        map = reseat(map);
        current_seated = total_occupied(map);
    }
    return previous_seated;
}

int main() {
    map_t test_map1{".#L", "###", "###"};
    assert(total_occupied(test_map1) == 7);
    assert(count_nearby_occupied(test_map1, 1, 0) == 3);
    map_t test_map2{
        "L.LL.LL.LL",
        "LLLLLLL.LL",
        "L.L.L..L..",
        "LLLL.LL.LL",
        "L.LL.LL.LL",
        "L.LLLLL.LL",
        "..L.L.....",
        "LLLLLLLLLL",
        "L.LLLLLL.L",
        "L.LLLLL.LL"};
    assert(first_solution(test_map2) == 37);


    const map_t map = read_stdin();
    uint32_t first = first_solution(map);
    //uint32_t second = second_solution(input);
    std::cout << "first answer: " << first << std::endl;
    //std::cout << "second answer: " << second << std::endl;
    assert(first == 2361 && "first solution doesn't match");
    //assert(second == 539 && "second solution doesn't match");
    return 0;
}
