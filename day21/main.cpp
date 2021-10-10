#include <vector>
#include <string>
#include <iostream>
#include <regex>
#include <set>
#include <iterator>
#include <cassert>
#include <algorithm>
#include <map>
#include <sstream>

std::vector<std::string> read_stdin() {
    std::vector<std::string> input;
    std::string line;
    while (std::getline(std::cin, line)) {
        input.push_back(line);
    }
    return input;
}

void remove_ingredient(const std::string &ingredient, std::map<std::string, std::set<std::string>> &allergens) {
    for (auto &allergen_pair : allergens) {
        if (allergen_pair.second.size() > 1) {
            allergen_pair.second.erase(ingredient);
        }
    }
}

int main() {
    std::vector<std::string> input = read_stdin();
    std::multiset<std::string> all_ingredients;
    std::map<std::string, std::set<std::string>> allergens;

    std::regex word_pattern(R"(\b\w+\b)");
    std::set<std::string> current_ingredients;
    for (auto &line : input) {
        current_ingredients.clear();
        bool it_allergens = false;
        auto word_it = std::sregex_iterator(line.begin(), line.end(), word_pattern);
        for (auto it = word_it; it != std::sregex_iterator(); ++it) {
            std::string match((*it).str());
            // Next matches are allergens.
            if (match == "contains") {
                it_allergens = true;
                continue;
            }
            if (it_allergens) {
                // This match is an allergen.
                auto [old_ingredients, new_insert] = allergens.emplace(match, current_ingredients);
                // If allergen does already has ingredients, then take
                // intersection of the new and old ingredients.
                if (!new_insert) {
                    std::set<std::string> intersection;
                    set_intersection(
                            std::begin(old_ingredients->second), std::end(old_ingredients->second),
                            std::begin(current_ingredients), std::end(current_ingredients),
                            std::inserter(intersection, std::begin(intersection)));
                    allergens[match] = std::move(intersection);
                }
            } else {
                // This match is an ingredient.
                all_ingredients.emplace(match);
                current_ingredients.emplace(std::move(match));
            }
        }
    }

    // Part 1.
    for (auto &allergen : allergens) {
        for (auto &ingredient : allergen.second) {
            all_ingredients.erase(ingredient);
        }
    }
    uint64_t first = all_ingredients.size();
    std::cout << "First answer: " << first << std::endl;
    assert(first == 2874 && "first solution doesn't match");

    // Part 2.
    while(std::any_of(std::begin(allergens), std::end(allergens),
                     [](auto &allergen_pair) { return allergen_pair.second.size() > 1; })) {
        for (auto &allergen_pair : allergens) {
            if (allergen_pair.second.size() == 1) {
                std::string ingredient = *std::begin(allergen_pair.second);
                remove_ingredient(ingredient, allergens);
            }
        }
    }
    std::stringstream dangerous_list;
    for (auto &allergen : allergens) {
        dangerous_list << *std::begin(allergen.second) << ",";
    }
    std::cout << "second answer: " << dangerous_list.str() << std::endl;
    assert(dangerous_list.str() == "gfvrr,ndkkq,jxcxh,bthjz,sgzr,mbkbn,pkkg,mjbtz," && "second solution doesn't match");
    return 0;
}
