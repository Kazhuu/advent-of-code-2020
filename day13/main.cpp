#include <cstdint>
#include <tuple>
#include <vector>
#include <iostream>
#include <cassert>
#include <numeric>

std::pair<uint32_t, std::vector<int32_t>> read_stdin() {
    uint32_t depart_timestamp = 0;
    std::vector<int32_t> bus_ids;
    std::string line;
    std::getline(std::cin, line);
    depart_timestamp = std::stoi(std::move(line));
    std::getline(std::cin, line);
    int32_t len = line.find(",");
    while (len != std::string::npos) {
        std::string id(line.substr(0, len));
        if (id != "x") {
            bus_ids.push_back(std::stoi(id));
        } else {
            bus_ids.push_back(-1);
        }
        line.erase(0, len + 1);
        len = line.find(",");
    }
    // Remember the last number if available.
    if (line != "x") {
        bus_ids.push_back(std::stoi(line));
    } else {
        bus_ids.push_back(-1);
    }
    return std::make_pair(depart_timestamp, bus_ids);
}

std::tuple<int64_t, int64_t, int64_t> extended_gcd(int64_t a, int64_t b)
{
    if (a == 0) { return std::make_tuple(b, 0, 1); }
    auto [gcdiv, x, y] = extended_gcd(b % a, a);
    return std::make_tuple(gcdiv, y - ((b / a) * x), x);
}

uint64_t first_solution(const uint32_t depart_timestamp, const std::vector<int32_t> &bus_ids) {
    uint32_t current_timestamp = depart_timestamp;
    while (true) {
        for (auto id : bus_ids) {
            if (id != -1 && current_timestamp % id == 0) {
                return (current_timestamp - depart_timestamp) * id;
            }
        }
        current_timestamp++;
    }
    return 0;
}

/**
 * This problem can be solved using Chinese remainder theorem:
 * https://en.wikipedia.org/wiki/Chinese_remainder_theorem and
 * https://www.youtube.com/watch?v=zIFehsBHB8o
 * Solution to part 2 is we are looking for x which is solution to all remainder
 * equations coming from all available bus IDs.
 * x = a1 (mod bus_id1);
 * x = a2 (mod bus_id2);
 * ...
 * x = an (mod bus_idn);
 * Where a1..an is array of remainders calculated by subtracting index of the bus (minutes
 * from the first bus) from its id.
 */
uint64_t second_solution(const std::vector<int32_t> &bus_ids) {
    std::vector<int64_t> ni;
    std::vector<int64_t> bi;
    for (int i = 0; i < bus_ids.size(); ++i) {
        if (bus_ids[i] != -1) {
            ni.push_back(bus_ids[i]);
            bi.push_back(bus_ids[i] - i);
        }
    }
    // N = n1*n2*n3*...*nk
    int64_t N = std::accumulate(ni.cbegin(), ni.cend(), (int64_t)1, std::multiplies<int64_t>());
    // Calculate x which is solution for all remainder equations.
    // x = sum of all bi*Ni*xi of all bus ids.
    int64_t x = 0;
    for (int i = 0; i < ni.size(); ++i) {
        // Ni = N / ni
        int64_t Ni = N / ni[i];
        auto [gc_div, xi, _] = extended_gcd(Ni, ni[i]);
        assert(gc_div == 1);
        x = (N + x + (bi[i] * Ni * xi)) % N;
    }
    return x;
}

int main() {
    assert(second_solution({17, -1 , 13, 19}) == 3417);

    const auto [depart_timestamp, bus_ids] = read_stdin();
    uint32_t first = first_solution(depart_timestamp, bus_ids);
    uint64_t second = second_solution(bus_ids);
    std::cout << "first answer: " << first << std::endl;
    std::cout << "second answer: " << second << std::endl;
    assert(first == 3966 && "first solution doesn't match");
    assert(second == 800177252346225 && "second solution doesn't match");
    return 0;
}
