#include <vector>
#include <string>
#include <iostream>
#include <cstdint>
#include <iterator>
#include <algorithm>
#include <cassert>

using map_t = std::vector<std::vector<std::vector<bool>>>;
using mapw_t = std::vector<std::vector<std::vector<std::vector<bool>>>>;

std::vector<std::string> read_stdin() {
    std::vector<std::string> input(
            (std::istream_iterator<std::string>(std::cin)),
            std::istream_iterator<std::string>());
    return input;
}

void print_map(const map_t &map) {
    const int64_t z_middle = map.size() / 2;
    for (int64_t z = 0; z < map.size(); ++z) {
        std::cout << "z=" << z - z_middle << std::endl;
        for (auto &line : map[z]) {
            for (auto tile : line) {
                if (tile) {
                    std::cout << '#';
                } else {
                    std::cout << '.';
                }
            }
            std::cout << std::endl;
        }
    }
}

uint64_t count_neigbours(const map_t &map, int64_t z, int64_t y, int64_t x) {
    int64_t nz = map.size();
    int64_t ny = map[0].size();
    int64_t nx = map[0][0].size();
    uint64_t count = 0;
    for (int64_t cz = std::max((int64_t)0, z - 1); cz < std::min(nz, z + 2); ++cz) {
        for (int64_t cy = std::max((int64_t)0, y - 1); cy < std::min(ny, y + 2); ++cy) {
            for (int64_t cx = std::max((int64_t)0, x - 1); cx < std::min(nx, x + 2); ++cx) {
                if (map[cz][cy][cx]) {
                    count++;
                }
            }
        }
    }
    if (map[z][y][x]) {
        count--;
    }
    return count;
}

uint64_t count_neigbours(const mapw_t &map, int64_t w, int64_t z, int64_t y, int64_t x) {
    int64_t nw = map.size();
    int64_t nz = map[0].size();
    int64_t ny = map[0][0].size();
    int64_t nx = map[0][0][0].size();
    uint64_t count = 0;
    for (int64_t cw = std::max((int64_t)0, w - 1); cw < std::min(nw, w + 2); ++cw) {
        for (int64_t cz = std::max((int64_t)0, z - 1); cz < std::min(nz, z + 2); ++cz) {
            for (int64_t cy = std::max((int64_t)0, y - 1); cy < std::min(ny, y + 2); ++cy) {
                for (int64_t cx = std::max((int64_t)0, x - 1); cx < std::min(nx, x + 2); ++cx) {
                    if (map[cw][cz][cy][cx]) {
                        count++;
                    }
                }
            }
        }
    }
    if (map[w][z][y][x]) {
        count--;
    }
    return count;
}

map_t simulate(const map_t &old_map) {
    int64_t nz = old_map.size();
    int64_t ny = old_map[0].size();
    int64_t nx = old_map[0][0].size();
    map_t new_map(nz, std::vector<std::vector<bool>>(ny, std::vector<bool>(nx, false)));
    for (int64_t z = 0; z < nz; ++z) {
        for (int64_t y = 0; y < ny; ++y) {
            for (int64_t x = 0; x < nx; ++x) {
                int64_t active = count_neigbours(old_map, z, y, x);
                if (old_map[z][y][x] && (active == 2 || active == 3)) {
                    new_map[z][y][x] = true;
                } else if (active == 3) {
                    new_map[z][y][x] = true;
                }
            }
        }
    }
    return new_map;
}

mapw_t simulate(const mapw_t &old_map) {
    int64_t nw = old_map.size();
    int64_t nz = old_map[0].size();
    int64_t ny = old_map[0][0].size();
    int64_t nx = old_map[0][0][0].size();
    mapw_t new_map(nw, std::vector<std::vector<std::vector<bool>>>(nz, std::vector<std::vector<bool>>(ny, std::vector<bool>(nx, false))));
    for (int64_t w = 0; w < nw; ++w) {
        for (int64_t z = 0; z < nz; ++z) {
            for (int64_t y = 0; y < ny; ++y) {
                for (int64_t x = 0; x < nx; ++x) {
                    int64_t active = count_neigbours(old_map, w, z, y, x);
                    if (old_map[w][z][y][x] && (active == 2 || active == 3)) {
                        new_map[w][z][y][x] = true;
                    } else if (active == 3) {
                        new_map[w][z][y][x] = true;
                    }
                }
            }
        }
    }
    return new_map;
}

uint64_t count_active(const map_t &map) {
    int64_t nz = map.size();
    int64_t ny = map[0].size();
    int64_t nx = map[0][0].size();
    uint64_t count = 0;
    for (int64_t z = 0; z < nz; ++z) {
        for (int64_t y = 0; y < ny; ++y) {
            for (int64_t x = 0; x < nx; ++x) {
                if (map[z][y][x]) {
                    count++;
                }
            }
        }
    }
    return count;
}

uint64_t count_active(const mapw_t &map) {
    int64_t nw = map.size();
    int64_t nz = map[0].size();
    int64_t ny = map[0][0].size();
    int64_t nx = map[0][0][0].size();
    uint64_t count = 0;
    for (int64_t w = 0; w < nw; ++w) {
        for (int64_t z = 0; z < nz; ++z) {
            for (int64_t y = 0; y < ny; ++y) {
                for (int64_t x = 0; x < nx; ++x) {
                    if (map[w][z][y][x]) {
                        count++;
                    }
                }
            }
        }
    }
    return count;
}
uint64_t first_solution(const std::vector<std::string> &input) {
    uint64_t turns = 6;
    uint64_t nx = (2 * turns) + input[0].size();
    uint64_t ny = (2 * turns) + input.size();
    uint64_t nz = (2 * turns) + 1;
    map_t map(nz, std::vector<std::vector<bool>>(ny, std::vector<bool>(nx, false)));
    for (int64_t y = 0; y < input.size(); ++y) {
        for (int64_t x = 0; x < input[0].size(); ++x) {
            map[turns][turns + y][turns + x] = input[y][x] == '#';
        }
    }
    for (uint64_t turn = 0; turn < turns; ++turn) {
        map = simulate(map);
    }
    return count_active(map);
}

uint64_t second_solution(const std::vector<std::string> &input) {
    uint64_t turns = 6;
    uint64_t nx = (2 * turns) + input[0].size();
    uint64_t ny = (2 * turns) + input.size();
    uint64_t nz = (2 * turns) + 1;
    uint64_t nw = (2 * turns) + 1;
    mapw_t map(nw, std::vector<std::vector<std::vector<bool>>>(nz, std::vector<std::vector<bool>>(ny, std::vector<bool>(nx, false))));
    for (int64_t y = 0; y < input.size(); ++y) {
        for (int64_t x = 0; x < input[0].size(); ++x) {
            map[turns][turns][turns + y][turns + x] = input[y][x] == '#';
        }
    }
    for (uint64_t turn = 0; turn < turns; ++turn) {
        map = simulate(map);
    }
    return count_active(map);
}

int main() {
    std::vector<std::string> input = read_stdin();
    uint64_t first = first_solution(input);
    uint64_t second = second_solution(input);
    std::cout << "first answer: " << first << std::endl;
    std::cout << "second answer: " << second << std::endl;
    assert(first == 304 && "first solution doesn't match");
    assert(second == 1868 && "second solution doesn't match");
    return 0;
}
