#include <cstdint>
#include <tuple>
#include <vector>
#include <iostream>

std::pair<uint32_t, std::vector<uint32_t>> read_stdin() {
    uint32_t depart_timestamp = 0;
    std::vector<uint32_t> lines;
    std::string line;
    std::getline(std::cin, line);
    depart_timestamp = std::stoi(std::move(line));
    std::getline(std::cin, line);
    int32_t len = line.find(",");
    while (len != std::string::npos) {
        std::string bus(line.substr(0, len));
        if (bus != "x") {
            lines.push_back(std::stoi(bus));
        }
        line.erase(0, len + 1);
        len = line.find(",");
    }
    // Remember the last number if available.
    if (line != "x") {
        lines.push_back(std::stoi(line));
    }
    return std::make_pair(depart_timestamp, lines);
}

uint64_t first_solution(uint32_t depart_timestamp, std::vector<uint32_t> &lines) {
    bool not_found = true;
    uint32_t depart_line = 0;
    uint32_t current_timestamp = depart_timestamp;
    do {
        current_timestamp++;
        for (auto line : lines) {
            if (current_timestamp % line == 0) {
                depart_line = line;
                not_found = false;
                break;
            }
        }
    } while (not_found);
    return (current_timestamp - depart_timestamp) * depart_line;
}

int main() {
    auto [depart_timestamp, lines] = read_stdin();
    uint32_t first = first_solution(depart_timestamp, lines);
    //uint64_t second = second_solution(input);
    std::cout << "first answer: " << first << std::endl;
    //std::cout << "second answer: " << second << std::endl;
    //assert(first == 2310 && "first solution doesn't match");
    //assert(second == 64793042714624 && "second solution doesn't match");
    return 0;
}
