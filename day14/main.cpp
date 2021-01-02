#include <numeric>
#include <vector>
#include <string>
#include <iostream>
#include <cstdint>
#include <unordered_map>
#include <regex>
#include <cassert>

const std::vector<std::string> read_stdin() {
    std::vector<std::string> input;
    std::string line;
    while (std::getline(std::cin, line)) {
        input.push_back(line);
    }
    return input;
}

std::pair<uint64_t, uint64_t> parse_mem_line(const std::string &line) {
    std::regex mem_pattern(R"(mem\[(\d+)\] = (\d+))");
    std::smatch mem_match;
    std::regex_search(line, mem_match, mem_pattern);
    return std::make_pair(std::stoul(mem_match[1]), std::stoul(mem_match[2]));
}

std::string parse_mask_line(const std::string &line) {
    std::regex mask_pattern(R"(mask = ([10X]+))");
    std::smatch mask_match;
    std::regex_search(line, mask_match, mask_pattern);
    return mask_match[1];
}

std::pair<uint64_t, uint64_t> make_masks(const std::string &mask_line) {
    std::string set_mask = mask_line;
    std::string clear_mask = mask_line;
    for (int i = 0; i < mask_line.size(); ++i) {
        if (mask_line[i] == 'X') {
            clear_mask[i] = '1';
        } else {
            clear_mask[i] = '0';
        }
        if (mask_line[i] == '1') {
            set_mask[i] = '1';
        } else {
            set_mask[i] = '0';
        }
    }
    return std::make_pair(std::stoul(clear_mask, 0, 2), std::stoul(set_mask, 0, 2));
}

uint64_t sum_memory(const std::unordered_map<uint64_t, uint64_t> &memory) {
    auto binary_op = [](const uint64_t sum, const auto &item) {
        return sum + item.second;
    };
    return std::accumulate(memory.begin(), memory.end(), (uint64_t)0, std::move(binary_op));
}

std::vector<uint64_t> generate_addresses(const std::string &mask, std::bitset<36> address) {
    // First apply the mask and collect the positions of floating bits in the
    // mask. Notice the reverse index order because of bitset zero index starts
    // from the rightmost index and string from the leftmost index.
    std::vector<uint64_t> floating_bits;
    for (int i = 0; i < mask.size(); ++i) {
        if (mask[i] == 'X') {
            floating_bits.push_back(mask.size() - i - 1);
        } else if (mask[i] == '1') {
            address[mask.size() - i - 1] = true;
        }
    }
    // Next generate all possible addresses from floating bits.
    std::vector<uint64_t> addresses;
    uint64_t address_count = 1u << floating_bits.size();
    for (uint64_t bits = 0; bits < address_count; ++bits) {
        std::bitset<36> new_address(address);
        for (uint64_t i = 0; i < floating_bits.size(); ++i) {
            new_address[floating_bits[i]] = (bits & (1u << i)) != 0;
        }
        addresses.push_back(new_address.to_ullong());
    }
    return addresses;
}


uint64_t first_solution(const std::vector<std::string> &input) {
    std::unordered_map<uint64_t, uint64_t> memory;
    int64_t clear_mask = 0;
    int64_t set_mask = 0;
    for (auto &line : input) {
        if (line[1] == 'e') {
            auto [address, value] = parse_mem_line(line);
            memory[address] = (value & clear_mask) | set_mask;
        } else {
            std::string mask = parse_mask_line(line);
            std::tie(clear_mask, set_mask) = make_masks(mask);
        }
    }
    return sum_memory(memory);
}

uint64_t second_solution(const std::vector<std::string> &input) {
    std::unordered_map<uint64_t, uint64_t> memory;
    std::string mask;
    for (auto &line : input) {
        if (line[1] == 'e') {
            auto [address, value] = parse_mem_line(line);
            std::vector<uint64_t> addresses = generate_addresses(mask, address);
            for (auto addr : addresses) {
                memory[addr] = value;
            }
        } else {
            mask = parse_mask_line(line);
        }
    }
    return sum_memory(memory);
}

int main() {
    const std::vector<std::string> input = read_stdin();
    uint64_t first = first_solution(input);
    uint64_t second = second_solution(input);
    std::cout << "first answer: " << first << std::endl;
    std::cout << "second answer: " << second << std::endl;
    assert(first == 10452688630537 && "first solution doesn't match");
    assert(second == 2881082759597 && "second solution doesn't match");
    return 0;
}
