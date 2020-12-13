#include <cassert>
#include <iostream>
#include <string>
#include <vector>

/**
 * Represents one parsed passport. User can check does it passport has all
 * fields and are they valid.
 */
class Passport {
public:
    Passport(std::string &&input)
        : birth_year(-1), issue_year(-1), expiration_year(-1) {
        parse_input(std::move(input));
    }

    bool has_all_fields() const {
        return (birth_year != -1 && issue_year != -1 && expiration_year != -1 &&
                height != "" && hair_color != "" && eye_color != "" && passport_id != "");
    }

    bool is_valid() const {
        if (!has_all_fields()) {
            return false;
        }
        bool birth_year_valid = birth_year >= 1920 && birth_year <= 2002;
        bool issue_year_valid = issue_year >= 2010 && issue_year <= 2020;
        bool expiration_year_valid = expiration_year >= 2020 && expiration_year <= 2030;
        bool height_valid = is_height_valid();
        bool hair_color_valid = is_hair_colod_valid();
        bool eye_color_valid = is_eye_color_valid();
        bool passport_id_valid = is_passport_id_valid();
        return birth_year_valid && issue_year_valid && expiration_year_valid && height_valid &&
            hair_color_valid && eye_color_valid && passport_id_valid;
    }

private:
    void parse_input(std::string &&input) {
        int32_t len = input.find(" ");
        while (len != std::string::npos) {
            parse_key_value(input.substr(0, len));
            // Erase parsed part including the white space.
            input.erase(0, len + 1);
            len = input.find(" ");
        }
    }

    void parse_key_value(std::string &&input) {
        std::string key = input.substr(0, 3);
        std::string value = input.substr(4, std::string::npos);
        if (key == "byr") {
            birth_year = std::stoi(value);
        } else if (key == "iyr") {
            issue_year = std::stoi(value);
        } else if (key == "eyr") {
            expiration_year = std::stoi(value);
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

    bool is_height_valid() const {
        bool valid = false;
        std::string unit = height.substr(height.size() - 2, height.size());
        uint32_t value = std::stoi(height.substr(0, height.size() - 2));
        if (unit == "cm") {
            valid = (value >= 150 && value <= 193);
        } else if (unit == "in") {
            valid = (value >= 59 && value <= 76);
        }
        return valid;
    }

    bool is_hair_colod_valid() const {
        bool valid = false;
        std::string value = hair_color.substr(1, hair_color.size());
        if (hair_color[0] == '#' && value.size() == 6) {
            // Would throw an error if contains invalid characters but it seems
            // puzzle input doesn't do this.
            std::stoi(value, 0, 16);
            valid = true;
        }
        return valid;
    }

    bool is_eye_color_valid() const {
        return (eye_color == "amb" || eye_color == "blu" || eye_color == "brn" || eye_color == "gry"
                || eye_color == "grn" || eye_color == "hzl" || eye_color == "oth");
    }

    bool is_passport_id_valid() const {
        bool valid = false;
        if (passport_id.size() == 9) {
            // Would throw an error if contains invalid characters but it seems
            // puzzle input doesn't do this.
            std::stoi(passport_id);
            valid = true;
        }
        return valid;
    }

    int32_t birth_year;
    int32_t issue_year;
    int32_t expiration_year;
    std::string height;
    std::string hair_color;
    std::string eye_color;
    std::string passport_id;
    std::string country_id;
};

/**
 * Parse stdin and construct vector containing Passport instances.
 */
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

uint32_t first_solution(const std::vector<Passport> &passports) {
    uint32_t valid_count = 0;
    for (auto &passport : passports) {
        if (passport.has_all_fields()) {
            valid_count++;
        }
    }
    return valid_count;
}

uint32_t second_solution(const std::vector<Passport> &passports) {
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
    uint32_t second = second_solution(passports);
    std::cout << "first answer: " << first << std::endl;
    std::cout << "second answer: " << second << std::endl;
    assert(first == 204 && "first solution doesn't match");
    assert(second == 179 && "second solution doesn't match");
    return 0;
}
