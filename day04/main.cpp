#include <cassert>
#include <iostream>
#include <string>
#include <vector>

class Passport {
public:
    Passport(std::string &&input) {
        parse_input(std::move(input));
    }

    bool is_valid() const {
        return (birth_year != "" && issue_year != "" && expiration_date != "" &&
                height != "" && hair_color != "" && eye_color != "" && passport_id != "");
    }

private:
    void parse_input(std::string &&input) {
        int32_t start_pos = 0;
        int32_t len = input.find(" ");
        while (len != std::string::npos) {
            parse_key_value(input.substr(0, len));
            // Erase parsed part including white space.
            input.erase(0, len + 1);
            len = input.find(" ");
        }
    }

    void parse_key_value(std::string &&input) {
        std::string key = input.substr(0, 3);
        std::string value = input.substr(4, std::string::npos);
        if (key == "byr") {
            birth_year = value;
        } else if (key == "iyr") {
            issue_year = value;
        } else if (key == "eyr") {
            expiration_date = value;
        } else if (key == "hgt") {
            height = value;
        } else if (key == "hcl") {
            hair_color = value;
        } else if (key == "ecl") {
            eye_color = value;
        } else if (key == "pid") {
            passport_id = value;
        } else if (key == "cid") {
            country_id = value;
        } else {
                std::cout << "unknown key" << std::endl;
        }
    }

    std::string birth_year;
    std::string issue_year;
    std::string expiration_date;
    std::string height;
    std::string hair_color;
    std::string eye_color;
    std::string passport_id;
    std::string country_id;
};

std::vector<Passport> parse_stdin() {
    std::vector<Passport> passports;
    std::string input = "";
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line != "") {
            input += line + " ";
        } else {
            passports.emplace_back(std::move(input));
            input = "";
        }
    }
    // Get the last passport because that one is not separated by empty line.
    passports.emplace_back(std::move(input));
    return passports;
}

int first_solution(const std::vector<Passport> &passports) {
    uint32_t valid_count = 0;
    for (auto &passport : passports) {
        if (passport.is_valid()) {
            valid_count++;
        }
    }
    return valid_count;
}

int main() {
    std::vector<Passport> passports = parse_stdin();
    uint32_t first = first_solution(passports);
    std::cout << "first answer: " << first << std::endl;
    assert(first == 204 && "first solution doesn't match");
    //assert(second == 388 && "second solution doesn't match");
    return 0;
}
